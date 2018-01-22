#include "stdafx.h"
#pragma once

Event& Game_Data::add_event(std::string s, std::vector<Flag> req, Room& r) {
	Room room = r;
	Event e(s, req, room);
	events.push_back(e);
	return events.back();
}

Event& Game_Data::add_event(std::string s, std::vector<Flag> req) {
	Event e(s, req);
	events.push_back(e);
	return events.back();
}

void Game_Data::add_puzzle(std::string name, Object use, Object used_on, Flag flag) {
	Puzzle temp(name, use, used_on, flag);
	puzzles.push_back(temp);
}

void Game_Data::add_puzzle(std::string name, Object use, Object used_on, Flag flag, std::vector<Flag> prereq) {
	Puzzle temp(name, use, used_on, flag, prereq);
	puzzles.push_back(temp);
}

void Game_Data::add_puzzle(std::string name, Object use, Object used_on, Flag flag, Room* lock, std::vector<Flag> prereq) {
	Puzzle temp(name, use, used_on, flag, lock, prereq);
	puzzles.push_back(temp);
}

void Game_Data::add_puzzle(std::string name, Object use, Object used_on, Flag flag, Room* lock) {
	Puzzle temp(name, use, used_on, flag, lock);
	puzzles.push_back(temp);
}

void Game_Data::add_verb(std::string name, int index) {
	Action tmp(name, index);
	action_list.push_back(tmp);
}

void Game_Data::connect_rooms(int id, Room& to, Room& from, std::string to_name, std::string from_name) {
	Door door_from(id, to_name, &to);
	Door door_to(id, (from_name == "" ? to_name : from_name), &from);
	to.add_door(door_to);
	from.add_door(door_from);
}

void Game_Data::connect_rooms(int id, Room& to, Room& from, std::string to_name, std::string from_name, std::vector<Flag*> door_lock) {
	Door door_from(id, to_name, &to, door_lock);
	Door door_to(id, (from_name == "" ? to_name : from_name), &from, door_lock);
	to.add_door(door_to);
	from.add_door(door_from);
}

std::string format(std::string s) {
	for (auto &c : s) c = tolower(c);
	return s;
}

bool Game_Data::is_locked(Door d) {
	for (auto el : d.lock) {
		if (std::find(flags_obtained.begin(), flags_obtained.end(), *el) == flags_obtained.end()) return true;
	}
	return false;
}

void lock_door(Door& door, std::vector<Flag*> lock) {
	door.add_lock(lock);
}

void Game_Data::make_dict() {
	std::ifstream is("dictionary");
	std::string word;
	while (getline(is, word)) {
		std::string pos;
		getline(is, pos);
		dict.insert({ word, pos });
	}
}

int member_of(std::string word, std::vector<std::string> list) {
	int cnt = 0;
	for (auto &c : word) c = tolower(c);
	for (auto el : list) {
		if (word.find(el) != std::string::npos) {
			return cnt;
		}
		cnt++;
	}
	return -1;
}

Object member_of(std::string word, std::vector<Object> list) {
	std::unique_ptr<Object> obj(new Object());
	for (auto &c : word) c = tolower(c);
	for (auto i = list.begin(); i != list.end(); i++)if (word.find(i->getname()) != std::string::npos) {
		return *i;
	}
	return *obj;
}

Room* member_of(std::string word, std::vector<Room*> list) {
	std::unique_ptr<Room> room(new Room());
	for (auto &c : word) c = tolower(c);
	for (auto i = list.begin(); i != list.end(); i++)if (word.find((*i)->getname()) != std::string::npos) {
		return *i;
	}
	return nullptr;
}


int Game_Data::transfer(std::vector<Object>& to, std::vector<Object>& from, Object obj) {
	if (std::find(to.begin(), to.end(), obj) != to.end()) {
		return 0;
	}
	auto it = std::find(from.begin(), from.end(), obj);
	to.push_back(*it);
	if (it != from.end()) {
		using std::swap;
		swap(*it, from.back());
		from.pop_back();
	}
	return 1;
}