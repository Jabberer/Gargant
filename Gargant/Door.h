#pragma once
class Door : public Token{
	Room *to;
public:
	std::vector<Flag*> lock;
	Door(int i, std::string s, Room* t) : Token(s), to(t) {}
	Door(int i, std::string s, Room* t, std::vector<Flag*> l) : Token(s), to(t), lock(l) {}
	Door() = default;
	Room* destination() { return to; }
	void(add_lock(std::vector<Flag*> l)) { lock = l; }
};