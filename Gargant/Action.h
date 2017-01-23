#pragma once
class Action : public Token {
public:
	static const int MOVE_INDEX = 0;
	static const int USE_INDEX = 1;
	static const int EXAMINE_INDEX = 2;
	static const int PICK_UP_INDEX = 3;
	static const int PUT_DOWN_INDEX = 4;
	std::pair<std::string, std::string> requirements;
	Action() : Action("", 0, {}) {}
	int index;
	Action(std::string s, int i, std::pair<std::string, std::string> req = { "","" })
		:Token(s,"action"),requirements(req), index(i) {}
};