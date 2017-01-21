#pragma once
class Event_Handler {
	Game_Data* state;
	std::string activate(Event&);
	bool check_req(Event);
public:
	std::string process_events();
	Event_Handler(Game_Data* s) : state(s) {}
	Event_Handler() = default;
};