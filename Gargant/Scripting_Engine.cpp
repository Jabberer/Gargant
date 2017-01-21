#include "stdafx.h"
#pragma once

void Scripting_Engine::update() {
	for (auto el : state.game_map) {
		assign(el);
	}
	for (auto &el : state.events) {
		assign(el);
	}
}

std::string Scripting_Engine::parse_line(std::ifstream& istream) {
	std::string word, temp;
	bool condition = true;
	while (istream >> word) {
		if (word == END) {
			return temp;
		}
		else {
			if (word[0] == '?') {
				condition = resolve_condition(word);
				istream >> word;
				word += " " + parse_line(istream);
			}
			if (condition) {
				if (temp == "" || temp.back() == ' ')
					temp += word;
				else temp += " " + word;
			}
			else condition = true;
		}
	}
}

Script Scripting_Engine::generate_script(std::string name) {
	Script script;
	std::string line, *focus = nullptr;
	std::ifstream istream("data");
	bool start = false;
	while (std::getline(istream, line)) {
		if (line == name) {
			start = true;
		}
		else if (start) {
			if (line == DESCRIPTION) {
				focus = &script.description;
			}
			else if (line == USE_TXT) {
				focus = &script.use_txt;
			}
			else if (line == USE_ERROR) {
				focus = &script.use_error;
			}
			else if (line == MOVE_ERROR) {
				focus = &script.move_error;
			}
			else if (line == PICK_UP_ERROR) {
				focus = &script.pick_up_error;
			}
			else if (line == PUT_DOWN_ERROR) {
				focus = &script.put_down_error;
			}
			else if (line == EVENT_TXT) {
				focus = &script.event_txt;
			}
			else if (line == END) {
				break;
			}
			if (focus != nullptr)
				*focus = parse_line(istream);
			focus = nullptr;
		}
	}
	return script;
}

bool Scripting_Engine::resolve_condition(std::string s) {
	std::vector<std::string> args;
	std::string word = "";
	std::string type, name;
	bool first = true;
	for (auto el : s) {
		if (word != "" && ispunct(el) && el != '_') {
			if (first) type = word;
			else name = word;
			word = "";
			first = false;
		}
		else if (!ispunct(el)) word += el;
		else if (el == '_') word += " ";
	}
	if (type == OBJECT) {
		for (auto el : state.current->room_objects) {
			if (caps(el.get_name()) == name) return true;
		}
	}
	else if (type == EVENT) {
		for (auto el : state.events) {
			if (caps(el.get_name()) == name && el.is_used()) return true;
		}
	}
	else if (type == FLAG) {
		for (auto el : state.flags_obtained) {
			if (caps(el.get_name()) == name) return true;
		}
	}
	return false;
}

std::string Scripting_Engine::format_name(std::string name) {
	std::string caps_name = caps(name);
	std::string formatted_name;
	for (auto el : caps_name) {
		if (el == ' ') formatted_name += "_";
		else formatted_name += el;
	}
	return formatted_name;
}

std::string Scripting_Engine::caps(std::string name) {
	std::string caps_name;
	for (auto el : name) {
		caps_name += toupper(el);
	}
	return caps_name;
}

void Scripting_Engine::assign(Room* room) {
	std::string name = "##ROOM::" + format_name(room->get_name()) + "##";
	room->assign_script(generate_script(name));
}

void Scripting_Engine::assign(Event& e) {
	std::string name = "##EVENT::" + format_name(e.get_name()) + "##";
	e.assign_script(generate_script(name));
}