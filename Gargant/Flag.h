#pragma once
class Flag: public Token{
public:
	Flag() = default;
	Flag(std::string s) : Token(s,"flag") {}
};