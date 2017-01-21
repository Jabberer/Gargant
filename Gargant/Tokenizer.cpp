#include "stdafx.h"
#pragma once

std::vector<std::string>Tokenizer::tokenize(Game_Data state) {
	std::vector<std::string> word_list;
	std::string word, next_word;
	bool first = true;
	for (auto el : input) {
		if (!iswspace(el) && first)
			word += el;
		else if (!iswspace(el) && !first)
			next_word += el;
		else {
			if (first) first = false;
			else if (find(state.word_pairs.begin(), state.word_pairs.end(), word + " " + next_word) != state.word_pairs.end()) {
				word_list.push_back(word + " " + next_word);
				word = next_word = "";
				first = true;
			}
			else {
				word_list.push_back(word);
				word = next_word;
				next_word = "";
			}

		}
	}
	if (find(state.word_pairs.begin(), state.word_pairs.end(), word + " " + next_word) != state.word_pairs.end())
		word_list.push_back(word + " " + next_word);
	else {
		if (word != "")word_list.push_back(word);
		if (next_word != "")word_list.push_back(next_word);
	}
	return word_list;
}