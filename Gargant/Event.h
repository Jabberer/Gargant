#pragma once
class Event: public Token{
	Room destination;
	std::vector<Flag> requirements;
	bool used = false;
	std::vector<Object> objects_produced;
	bool win = false;
public:
	void use() { used = true; }
	std::string get_txt() { return data.event_txt; }
	Event(std::string s, std::vector<Flag> req) : Token(s), requirements(req){}
	Event(std::string s, std::vector<Flag> req, Room r) :Token(s), requirements(req), destination(r){}
	void make_victory() { win = true; }
	bool win_condition() { return win; }
	std::vector<Object> collect() { return objects_produced; }
	bool is_used() { return used; }
	std::vector<Flag> get_req() { return requirements; }
	Room get_dest() { return destination; }
	Event() = default;
};