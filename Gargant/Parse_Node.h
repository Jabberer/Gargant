#pragma once

class Parse_Node {
	char pos = '?';
public:
	std::vector<Parse_Node*> adj_nodes;
	Parse_Node() = default;
	Parse_Node(char c) : pos(c) {}
	bool connected_to(Parse_Node);
	char get_pos() const { return pos; }
	void add_node(Parse_Node &n) { adj_nodes.push_back(&n); }

};