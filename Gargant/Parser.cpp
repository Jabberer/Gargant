#include "stdafx.h"
#pragma once

std::vector<std::pair<std::string, std::string>> Parser::parse(std::vector<std::string> pos_list, std::vector<std::string> word_list) {
	auto pos = verify_syntax(pos_list);
	if (size(pos) - 1 != pos_list.size()) return{ { "","" } };
	std::vector<std::pair<std::string, std::string>> bound_list;
	for (int i = 0; i < pos_list.size(); i++) {
		std::string fuck = pos.substr(i, 1);
		if (fuck == "N" || fuck == "t" || fuck == "i" || fuck == "R" || fuck == "d" || fuck == "A")
			bound_list.push_back({ word_list[i], fuck });
	}
	return bound_list;
}


std::string Parser::verify_syntax(std::vector<std::string> unparsed) {
	unparsed.push_back("S");
	return verify_syntax(BEGIN, unparsed, "");
}

std::string Parser::verify_syntax(char pos, std::vector<std::string> unparsed, std::string parse_path = "") {
	if (pos == END) return parse_path;
	auto beg = unparsed.begin();
	std::string possible_pos = find_pos(pos, *beg);
	std::vector<std::string> newvec(++beg, unparsed.end());
	for (auto pos : possible_pos) {
		std::string passer = verify_syntax(pos, newvec, parse_path + pos);
		if (passer != "")return passer;
	}
	return"";
}


bool Parser::path_to(char c1, char c2) {
	Parse_Node n1, n2;
	n1 = find(c1);
	n2 = find(c2);
	return n1.connected_to(n2);
}

bool Parse_Node::connected_to(Parse_Node n) {
	for (auto node : adj_nodes) {
		if (node->get_pos() == n.get_pos()) return true;
	}
	return false;
}


Parse_Node& Parser::find(char c) {
	for (auto &el : node_graph) {
		if (el.get_pos() == c) {
			return el;
		}
	}
	return NULL_NODE;
}

int levenshtein_distance(const std::string &s1, const std::string &s2)
{
	// To change the type this function manipulates and returns, change
	// the return type and the types of the two variables below.
	int s1len = s1.size();
	int s2len = s2.size();

	auto column_start = (decltype(s1len))1;

	auto column = new decltype(s1len)[s1len + 1];
	std::iota(column + column_start, column + s1len + 1, column_start);

	for (auto x = column_start; x <= s2len; x++) {
		column[0] = x;
		auto last_diagonal = x - column_start;
		for (auto y = column_start; y <= s1len; y++) {
			auto old_diagonal = column[y];
			auto possibilities = {
				column[y] + 1,
				column[y - 1] + 1,
				last_diagonal + (s1[y - 1] == s2[x - 1] ? 0 : 1)
			};
			column[y] = std::min(possibilities);
			last_diagonal = old_diagonal;
		}
	}
	auto result = column[s1len];
	delete[] column;
	return result;
}


void Parser::directed_edge(char c1, char c2) {
	Parse_Node &n1 = find(c1);
	Parse_Node &n2 = find(c2);
	Parse_Node null_node;
	if (n1.get_pos() != null_node.get_pos() &&
		n2.get_pos() != null_node.get_pos()) {
		n1.add_node(n2);
	}
}

std::string Parser::find_pos(char pos, std::string s) {
	std::string s2;
	for (auto c : s) {
		if (path_to(pos, c)) s2 += c;
	}
	return s2;
}
