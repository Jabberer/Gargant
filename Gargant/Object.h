#pragma once

class Puzzle;
class Object : public Token {
public:
	std::vector<std::string> attributes;
	void add_attribute(std::string s) { attributes.push_back(s); }
	bool can_carry = true;
	std::string type;
	void update_description(std::string s);
	std::string getname() { return name; };
	Object() = default;
	Object(std::string name, std::vector<std::string> a, std::string t, bool b) :Token(name), can_carry(b), attributes(a), type(t) {}
};