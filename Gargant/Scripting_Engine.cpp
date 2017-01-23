#include "stdafx.h"
#pragma once

void Scripting_Engine::update() {
	assign(state.current);
	for (auto &el : state.current->doors) {
		assign(el);
	}
	for (auto &el : state.events) {
		assign(el);
	}
	for (auto &el : state.inventory) {
		assign(el);
	}
	for (auto &el : state.current->room_objects) {
		assign(el);
	}
}

std::string Scripting_Engine::parse_line(std::ifstream& istream, bool prev_condition = true) {
	std::string word, true_txt, false_txt;
	bool condition = true, txt_switch = true;
	while (istream >> word) {
		if (word == END) {
			return prev_condition? true_txt : false_txt;
		}
		else if (word == CONDITIONAL) {
			txt_switch = !txt_switch;
		}
		else {
			if (word[0] == '?') {
				condition = resolve_condition(word);
				word = "";
				word += parse_line(istream,condition);
			}
			if (txt_switch==true) {
				if (true_txt == "" || true_txt.back() == ' ')
					true_txt += word;
				else true_txt += " " + word;
			}
			else if (txt_switch == false) {
				if (false_txt == "" || false_txt.back() == ' ')
					false_txt += word;
				else false_txt += " " + word;
			}
			else condition = true;
		}
	}
}

void Scripting_Engine::resolve_queries(std::string& s) {
	size_t pos = s.find(QUERY_DESTINATION);
	if (pos != s.npos)
	s.replace(pos, size(QUERY_DESTINATION), state.current->get_name());
}

void Scripting_Engine::resolve_errors(std::string &s) {
	std::stringstream sstream(s);
	std::string temp, newstr, goo;
	sstream >> temp;
	sstream >> goo;
	if (temp.find(ERROR) != temp.npos) {
		if (sstream.eof()) {
			s = "You can't do that";
		}
		else {
			newstr = s.substr(temp.size());
			size_t beg_pos = newstr.find(temp);
			if (beg_pos != newstr.npos) {
				temp = newstr.substr(beg_pos + temp.size() + 1);
				size_t end_pos = temp.find_first_of("//");
				s = temp.substr(0, end_pos);
			}
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
			else if (line == MOVE_TXT) {
				focus = &script.move_txt;
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
	std::string name = "--ROOM::" + format_name(room->get_name()) + "--";
	room->assign_script(generate_script(name));
}

void Scripting_Engine::assign(Event& e) {
	std::string name = "--EVENT::" + format_name(e.get_name()) + "--";
	e.assign_script(generate_script(name));
}

void Scripting_Engine::assign(Door& door) {
	std::string name = "--DOOR::" + format_name(door.get_name()) + "--";
	door.assign_script(generate_script(name));
}

void Scripting_Engine::assign(Object& obj) {
	std::string name = "--OBJECT::" + format_name(obj.get_name()) + "--";
	obj.assign_script(generate_script(name));
}