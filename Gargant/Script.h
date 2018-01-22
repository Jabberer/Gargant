#pragma once
class Script {
public:
	std::string 
		description,
		use_txt,
		use_error,
		move_error,
		pick_up_error,
		put_down_error,
		event_txt;
	Script() = default;
	Script(std::string d) : description(d) {}
};