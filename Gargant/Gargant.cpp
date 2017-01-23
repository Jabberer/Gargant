// Gargant.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#pragma once
int main() {
	Game_Data game_state;
	game_state.make_dict();
	Parser p;
	Binder b(&game_state);
	std::string room_description, command_respone, event_txt;
	Scripting_Engine scripting_engine(game_state);
	Event_Handler event_handler(&game_state);
	scripting_engine.update();
	auto &dict = game_state.dict;
	bool quit = false;
	int height = 600;
	int location = 0;
	sf::Time time;
	sf::Clock clock;
	bool curs_blink = true;
	std::string input;
	sf::String output;
	room_description = b.examine() + '\n';
	sf::RenderWindow window;
	window.setVerticalSyncEnabled(true);
	window.create(sf::VideoMode(1280, 720), "Gargant");
	sf::Font font;
	int line = 0;
	if (!font.loadFromFile("arial.ttf"))
	{
		window.close();
	}
	sf::Text input_text(input, font, 24);
	sf::Text output_text(output, font, 24);
	output = event_handler.process_events();
	int bottom_bound = window.getSize().y - window.getSize().y / 100 - input_text.getCharacterSize();
	input_text.setPosition(0, bottom_bound);
	sf::RectangleShape cursor(sf::Vector2f(10, 8));
	cursor.setPosition(sf::Vector2f(0, bottom_bound + 23));
	cursor.setFillColor(sf::Color::White);
	bool ready_to_parse = false, state_changed = true;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type) {
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (event.key.code == sf::Keyboard::Return) {
					output.clear();
					ready_to_parse = true;
					line = 0;
				}
				break;
			case sf::Event::TextEntered:
				curs_blink = true;
				clock.restart();
				switch (event.text.unicode) {
				case 8:
					if (size(input)) {
						input.pop_back();
					}
					break;
				default:
					input += static_cast<char>(event.text.unicode);
					break;

				}
				break;
			}
		}
		time = clock.getElapsedTime();
		if (time.asMilliseconds() > 550) {
			clock.restart();
			curs_blink = !curs_blink;
		}

		std::vector<std::string> parselist, wordlist;
		scripting_engine.update();
		if (ready_to_parse) {
			if (size(input) > 1) {
				Tokenizer tok(input);
				auto tokenized_list = tok.tokenize(game_state);
				bool failed_parse = false, valid_phrase = true;
				for (auto iter = tokenized_list.begin(); iter != tokenized_list.end(); iter++) {
					std::string word = format(*iter);
					auto key = dict.find(word);
					if (key != dict.end()) {
						parselist.push_back(key->second);
						wordlist.push_back(key->first);
					}
					else {
						std::pair<std::string, std::string> correction;
						int min_distance = 10;
						for (auto el : dict) {
							int string_dif = levenshtein_distance(word, el.first);
							if (string_dif < min_distance) {
								correction = el;
								min_distance = string_dif;
							}
						}
						if (min_distance > 5) {
							command_respone = "I don't know what " + *iter + " means";
							failed_parse = true;
							break;
						}
						else if (min_distance > 1) {
							command_respone = "Did you mean " + correction.first + "?";
							failed_parse = true;
							break;
						}
						else {
							parselist.push_back(correction.second);
							wordlist.push_back(correction.first);
						}
					}
				}
				if (!failed_parse) {
					auto parsed_phrase = p.parse(parselist, wordlist);
					valid_phrase = p.verify(parsed_phrase);
					command_respone = ((valid_phrase) ? "" : "I don't know what that means");
					if (valid_phrase) {
						command_respone = b.bind(parsed_phrase);
					}
				}
			}
			scripting_engine.update();
			event_txt = event_handler.process_events();
			if (event_txt != "")
				event_txt += "\n\n";
			scripting_engine.resolve_errors(command_respone);
			scripting_engine.resolve_queries(command_respone);
			room_description = b.examine() + "\n\n";
			output = event_txt + room_description + command_respone;
			input = "";
			std::string s = output;
		}
		unsigned int text_width = 0;
		for (int j = line; line < output.getSize(); line++) {
			if (output[line] == '\n') 
				text_width = 0;
			sf::Glyph g = font.getGlyph(output[line], output_text.getCharacterSize(),false);
			if (iswspace(output[line]) && output[line] != '\n')
				j = line;
				text_width += g.advance;
			if (text_width > window.getSize().x) {
				line = j+1;
				output.insert(line, '\n');
				text_width = 0;
			}
		}
		ready_to_parse = false;
		window.clear(sf::Color::Black);
		input_text.setString(input);
		output_text.setString(output);
		int input_right_bound = window.getSize().x - input_text.getLocalBounds().width - cursor.getLocalBounds().width - 4;
		int output_upper_bound = window.getSize().y - output_text.getLocalBounds().height - input_text.getCharacterSize() * 2;
		if (output_upper_bound > 0)
			output_upper_bound = 0;
		if (input_right_bound > 0)
			input_right_bound = 0;
		input_text.setPosition(input_right_bound, bottom_bound);
		output_text.setPosition(0, output_upper_bound);
		int cursor_right_bound = input_text.getLocalBounds().width + 2;
		if (cursor_right_bound > window.getSize().x)
			cursor_right_bound = cursor_right_bound + input_right_bound;
		cursor.setPosition(cursor_right_bound, bottom_bound + 23);
		window.draw(input_text);
		window.draw(output_text);
		if (curs_blink)
			window.draw(cursor);
		window.display();
	}
	return 0;
}