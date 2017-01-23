#pragma once
class Scripting_Engine {
	const std::string EVENT = "EVENT";
	const std::string OBJECT = "OBJECT";
	const std::string CONTAINER = "CONTAINER";
	const std::string DOOR = "DOOR";
	const std::string ROOM = "ROOM";
	const std::string FLAG = "FLAG";
	const std::string DESCRIPTION = "##DESCRIPTION##";
	const std::string USE_TXT = "##USE_TXT##";
	const std::string MOVE_TXT = "##MOVE_TXT##";
	const std::string USE_ERROR = "##USE_ERROR##";
	const std::string MOVE_ERROR = "##MOVE_ERROR##";
	const std::string PICK_UP_ERROR = "##PICK_UP_ERROR##";
	const std::string PUT_DOWN_ERROR = "##PUT_DOWN_ERROR##";
	const std::string EVENT_TXT = "##EVENT_TXT##";
	const std::string END = "##END##";
	const std::string CONDITIONAL = ":";
	const std::string QUERY_DESTINATION = "!DESTINATION!";
	const std::string ERROR = "//ERROR::";
	Game_Data& state;
	void assign(Object&);
	void assign(Container&);
	void assign(Door&);
	void assign(Event&);
	void assign(Room*);
	bool resolve_condition(std::string);
	Script generate_script(std::string);
	std::string parse_line(std::ifstream&,bool);
public:
	static std::string caps(std::string);
	static std::string format_name(std::string);
	void update();
	Scripting_Engine() = default;
	Scripting_Engine(Game_Data& g) : state(g) {}
	void resolve_queries(std::string&);
	void resolve_errors(std::string&);
};