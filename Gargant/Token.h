#pragma once

class Token {
	friend int generate_id();
	friend bool operator== (const Token& lhs, const Token& rhs);
	friend void advance_state(Token& tok);
protected:
	Token(std::string s, std::string t) : name(s), classifier(t) { id = generate_id(); }
	std::string name = "";
	std::string classifier;
	int state = 0;
public:
	std::string get_classifier() { return classifier; }
	std::string describe() { return data.description; }
	Script data;
	int id = -1;
	std::string get_name() { return name; }
	Token() = default;
	void assign_script(Script &s) { data = s; }
};