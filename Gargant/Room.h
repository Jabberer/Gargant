#pragma once
class Object;
class Door;
class Room: public Token{
public:
	std::vector<Door> doors;
	std::vector<Object> room_objects;
	int getid() const { return id; }	
	void advance_state() { ++state; }
	void add_object(Object &obj) { room_objects.push_back(obj); }
	void add_door(Door d) { doors.push_back(d); }
	std::vector<Object> get_objects() const { return room_objects; }
	std::string getname() const { return name; }
	Room() : Room("") {}
	Room(std::string s):Token(s,"room")  {}
	};