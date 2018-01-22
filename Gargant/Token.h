#pragma once

class Token {
	friend int generate_id();
	friend bool operator== (const Token& lhs, const Token& rhs);
	friend void advance_state(Token& tok);
protected:
	Token(std::string s) : name(s){ id = generate_id(); }
	std::string name = "";
	int state = 0;
public:
	std::string describe() { return data.description; }
	Script data;
	int id = -1;
	std::string get_name() { return name; }
	Token() = default;
	void assign_script(Script &s) { data = s; }
};