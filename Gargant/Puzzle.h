#pragma once
class Flag;
class Room;
class Object;
class Game_Data;
class Puzzle {
	std::string name;
	Object use, used_on;
	std::vector<Flag> prereq;
	Flag flag;
	bool unary = false;
	bool solved = false;
	bool match(Object& u, Object& uo) { return u == use && uo == used_on; }
	bool check_prereq(Game_Data& state);
public:
	Puzzle() = default;
	Puzzle(std::string s, Object& u, Object& uo, Flag f) : name(s), use(u), used_on(uo), flag(f) {}
	Puzzle(std::string s, Object& u, Object& uo, Flag f, std::vector<Flag> p) : name(s), use(u), used_on(uo), prereq(p), flag(f) {}
	Puzzle(std::string s, Object& u, Object& uo, Flag f, Room* r) : name(s), use(u), used_on(uo), flag(f){}
	Puzzle(std::string s, Object& u, Object& uo, Flag f, Room* r, std::vector<Flag> p) : name(s), use(u), used_on(uo), flag(f), prereq(p) {}
	bool solve(Game_Data&, Object&, Object&);
	bool solve(Object&);
	bool is_solved() { return solved; }
	Flag get_flag() { return flag; }
};