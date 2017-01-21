#pragma once
#pragma once
class Tokenizer {
	std::string input;
public:
	Tokenizer() = default;
	std::vector<std::string>tokenize(Game_Data state);
	Tokenizer(std::string s) : input(s) {}

};