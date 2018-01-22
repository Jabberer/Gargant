#include "stdafx.h"
#pragma once

std::string Binder::bind(std::vector<std::pair<std::string, std::string>> parsed_list) {
	std::vector<std::pair<Token*, std::string>> token_list;
	std::vector<std::pair<std::string, std::string>> object_data;
	for (auto el : parsed_list) {
		if (el.second == "t" || el.second == "i") {
			token_list.push_back({ get_Action(el.first),"action" });
		}
		else if (el.second == "N") {
			object_data.push_back(el);
			Object* obj = get_Object(object_data);
			token_list.push_back({ obj,"object" });
			object_data = {};
		}
		else if (el.second == "R") {
			Room* room = get_Room(el.first);
			token_list.push_back({ room,"room" });
		}
		else if (el.second == "d") {
			Door* door = get_Door(el.first);
			token_list.push_back({ door,"door" });
		}
		else if (el.second == "A") {
			object_data.push_back(el);
		}
	}
	return call(token_list);
}

std::string Binder::call(std::vector<std::pair<Token*, std::string>> args) {
	auto iter = args.begin();
	Action *act = static_cast<Action *>(iter->first);
	std::vector<Object*> objects;
	iter++;
	for (auto beg = iter; beg != args.end(); beg++) {
		if (beg->second == "object") {
			Object *obj = static_cast<Object *>(beg->first);
			objects.push_back(obj);
		}
	}
	if (args.size() == 1) return translate(*act);
	else if (objects.size() == 1) {
		auto obj_iter = *objects.begin();
		return translate(*act, obj_iter);
	}
	else if (objects.size() == 2) {
		auto obj_iter = objects.begin();
		auto *obj = *obj_iter++;
		auto obj2 = *obj_iter;
		return translate(*act, obj, obj2);
	}
	else if (iter->second == "room") {
		Room *room = static_cast<Room *>(iter->first);
		if (args.size() - 1 == 1) {
			return translate(*act, room);
		}
	}
	else if (iter->second == "door") {
		Door *door = static_cast<Door *>(iter->first);
		if (args.size() - 1 == 1) {
			return translate(*act, door);
		}
	}
	return "";
}

std::string Binder::translate(Action& act, Object* obj) {
	switch (act.index) {
	case Action::PICK_UP_INDEX: return pick_up(obj);
		break;
	case Action::PUT_DOWN_INDEX: return put_down(obj);
		break;
	case Action::EXAMINE_INDEX: return examine(obj);
		break;
	}
}

std::string Binder::translate(Action& act, Object* obj, Object* obj2) {
	switch (act.index) {
	case Action::USE_INDEX:
		return use(obj, obj2);
		break;
	}
}
std::string Binder::translate(Action& act, Room* room) {
	switch (act.index) {
	case Action::EXAMINE_INDEX: return examine(room);
		break;
	case Action::MOVE_INDEX: return move(room);
		break;
	}
}

std::string Binder::translate(Action& act, Door* door) {
	switch (act.index) {
	case Action::EXAMINE_INDEX: return examine(door);
		break;
	case Action::MOVE_INDEX: return move(door);
		break;
	case Action::USE_INDEX: return move(door);
		break;
	case Action::PICK_UP_INDEX: return pick_up(door);
		break;
	case Action::PUT_DOWN_INDEX: return put_down(door);
		break;
	}
}

std::string Binder::translate(Action& act) {
	switch (act.index) {
	case Action::EXAMINE_INDEX:
		//		examine(std::cout);
		return "";
		break;
	}
}

std::string Binder::examine() {
	return examine(state->current);
}

std::string Binder::examine(Room* room) {
	if (room == nullptr) return "Looks like nothing to me";
	return room->describe();
}
std::string Binder::examine(Object* obj) {
	if (obj == nullptr) return "Looks like nothing to me";
	return obj->describe();
}
std::string Binder::examine(Door* door) {
	if (door == nullptr) return "Looks like nothing to me";
	return door->describe();
}
std::string Binder::move(Room* destination) {
	if (state->current == destination) return "You're already in " + destination->getname();
	if (destination == nullptr) return "You can't go there";
	Door* door = nullptr;
	for (auto &el : state->current->doors) {
		if (destination == el.destination()) door = &el;
	}
	return move(door);
}

std::string Binder::move(Door* door) {
	if (door == nullptr) return "You can't go there";
	if (state->is_locked(*door)) return "The door is locked";
	state->current = door->destination();
	return "You have moved to the " + door->destination()->get_name() + "\n";
}

std::string Binder::pick_up(Object* obj) {
	if (obj == nullptr) return "I don't see anything like that around";
	else {
		Object temp = *obj;
		if (!obj->can_carry) return "You can't pick that up";
		else if (state->transfer(state->inventory, state->current->room_objects, *obj)) {
			return "You have picked the " + temp.getname() + " up";
		}
		else return "You already have the " + temp.getname();
	}
}

std::string Binder::pick_up(Door*) {
	return "You... cannot pick that up";
}

std::string Binder::put_down(Object* obj) {
	if (obj == nullptr) return "I don't have anything like that";
	else {
		Object temp = *obj;
		if (state->transfer(state->current->room_objects, state->inventory, *obj))
			return "You have put down the " + temp.getname();
		else return "You are not carrying the " + temp.getname();
	}
}
std::string Binder::put_down(Door*) {
	return "You did it, it's... still on the ground. Yaaaaay.";
}

std::string Binder::use(Object* use) {
	return "advfawdvqefv";
}

std::string Binder::use(Object* use, Object* used_on) {
	if (use == nullptr || used_on == nullptr) return "Well I don't know about that...";
	for (auto& puzzle : state->puzzles) {
		if (puzzle.solve(*state, *use, *used_on)) {
			state->flags_obtained.push_back(puzzle.get_flag());
			return "You used " + use->getname() + " on " + used_on->getname();
		}
	}
	return "You can't use " + use->getname() + " on " + used_on->getname();
}

std::string Binder::use(Container* use) {
	if (use == nullptr) return "Well I don't know about that...";
	else {
		use->toggle();
		return use->data.use_txt;
	}
}

std::vector<Object*> Binder::pool_objects() {
	std::vector<Object*> object_list;
	for (auto &el : state->inventory) {
		object_list.push_back(&el);
	}
	for (auto &el : state->current->room_objects) {
		object_list.push_back(&el);
	}
	return object_list;
}

Action* Binder::get_Action(std::string name) {
	for (auto &el : state->action_list) {
		if (el.getname() == name) {
			return &el;
		}
	}
	return nullptr;
}

Door* Binder::get_Door(std::string name) {
	for (auto &el : state->current->doors) {
		if (el.get_name() == name) {
			return &el;
		}
	}
	return nullptr;
}
Object* Binder::get_Object(std::vector<std::pair<std::string, std::string>> object_data) {
	std::vector<Object*> object_list = pool_objects();
	std::string name;
	for (auto el : object_data) {
		if (name != "")name += " ";
		name += el.first;
	}
	for (auto el : object_list) {
		if (el->get_name() == name) return el;
	}
	return get_Object(object_data, object_list);
}

Object* Binder::get_Object(std::vector<std::pair<std::string, std::string>> object_data, std::vector<Object*> object_list) {
	std::vector<Object*> filtered_list;
	auto iter = object_data.begin();
	if (iter == object_data.end()) return nullptr;
	else if (iter->second == "A") {
		for (auto el : object_list) {
			if (std::find(el->attributes.begin(), el->attributes.end(), iter->first) != el->attributes.end()) {
				filtered_list.push_back(el);
			}
		}
		return get_Object(std::vector<std::pair<std::string, std::string>>(++iter, object_data.end()), filtered_list);
	}
	else if (iter->second == "N") {
		for (auto el : object_list) {
			if (el->type == iter->first) {
				filtered_list.push_back(el);
			}
		}
		if (filtered_list.size() == 1) {
			return *filtered_list.begin();
		}
		else {
			return nullptr;
		}
	}
	else return nullptr;
}

Room* Binder::get_Room(std::string name) {
	if (name == state->current->getname()) return state->current;
	for (auto &el : state->current->doors) {
		if (el.destination()->getname() == name) {
			return el.destination();
		}
	}
	return nullptr;
}