#pragma once

class Puzzle;
class Object : public Token {
	std::string type;
public:
	std::string get_type() { return type; }
	std::vector<std::string> attributes;
	void add_attribute(std::string s) { attributes.push_back(s); }
	bool can_carry = true;
	std::string getname() { return name; };
	Object() : Object("", {}, "", false) {}
	Object(std::string name, std::vector<std::string> a, std::string t, bool b) :Token(name,"object"), can_carry(b), type(t), attributes(a){}
};