#include "stdafx.h"
#pragma once
Room home("home");
Room hallway("hallway");
Room locked_room("locked room");
Room goal("goal");
Object golden_key("gold key", { "golden", "brass" }, "key", true);
Object red_key("red key", { "red", "stone" }, "key", true);
Object green_key("green key", { "green", "stone","copper" }, "key", true);
Object door("door", { "locked" }, "door", false);
Flag unlocked_door("unlocked door");
Event begin("begin", {}, home);
Event unlock_door("unlock door", { unlocked_door });
Event victory("win", { unlocked_door }, goal);
void Game_Data::init() {
	events.push_back(begin);
	events.push_back(unlock_door);
	victory.make_victory();
	events.push_back(victory);
	connect_rooms(0, home, hallway, "archway");
	connect_rooms(0, hallway, locked_room, "wooden door");
	connect_rooms(0, locked_room, goal, "secure door", "", { &unlocked_door });
	home.add_object(golden_key);
	home.add_object(green_key);
	home.add_object(red_key);
	locked_room.add_object(door);
	add_puzzle("lock", golden_key, door, unlocked_door, &goal);
	current = &home;
	game_map.push_back(&home);
	game_map.push_back(&hallway);
	game_map.push_back(&locked_room);
	add_verb("examine", Action::EXAMINE_INDEX);
	add_verb("pick up", Action::PICK_UP_INDEX);
	add_verb("put down", Action::PUT_DOWN_INDEX);
	add_verb("move", Action::MOVE_INDEX);
	add_verb("use", Action::USE_INDEX);
}