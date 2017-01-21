#pragma once
class Parse_Node;
class Parser {
	Parse_Node NULL_NODE;
	std::vector<char> pos_list;
	std::vector<Parse_Node> node_graph;
	void init();
	void directed_edge(char c1, char c2);
	bool path_to(char, char);
	std::string Parser::find_pos(char, std::string);
	Parse_Node& find(char c);

public:
	const char BEGIN = 'B';
	const char	NOUN = 'N';
	const char	PLURAL = 'P';
	const char	NOUN_PHRASE = 'h';
	const char	VERB_PARTICIPLE = 'V';
	const char	VERB_TRANSITIVE = 't';
	const char	VERB_INTRANSITIVE = 'i';
	const char	ADJ = 'A';
	const char	ADV = 'v';
	const char	CONJUNCTION = 'C';
	const char	PREPOSITION = 'P';
	const char	INTERJECTION = '!';
	const char	PRONOUN = 'r';
	const char ROOM = 'R';
	const char DOOR = 'd';
	const char	DEFINITE_ARTICLE = 'D';
	const char	INDEFINITE_ARTICLE = 'I';	
	const char	NOMINATIVE = 'o';
	const char END = 'S';
	const char NULL_POS = '?';
	std::string verify_syntax(char, std::vector<std::string>,std::string);
	std::string verify_syntax(std::vector<std::string> unparsed);
	bool verify(std::vector<std::pair<std::string,std::string>> s) { return s[0].second != ""; }
	std::vector<std::pair<std::string, std::string>> parse(std::vector<std::string>, std::vector<std::string>);
	Parser() { init(); }
};
int levenshtein_distance(const std::string &s1, const std::string &s2);