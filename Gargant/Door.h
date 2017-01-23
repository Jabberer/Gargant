#pragma once
class Door : public Token{
	Room *to;
public:
	std::vector<Flag*> lock;
	Door(int i, std::string s, Room* t, std::vector<Flag*> l = {}) : Token(s, "door"), to(t), lock(l) {}
	Door() : Door(0, "",nullptr) {}
	Room* destination() { return to; }
	void(add_lock(std::vector<Flag*> l)) { lock = l; }
};