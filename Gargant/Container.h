#pragma once
class Container : public Object {
	friend void advance_state(Container&);
	std::vector<Object> contains;
	bool open = false;
public:
	void add_object(Object o) { contains.push_back(o); }
	void toggle() { (open ? open = false : open = true); }
	bool is_open() { return open; }
	Container(std::string s, bool b, std::vector<Object>obj_list, std::vector<std::string> attributes, std::string type) :Object(s, attributes, type, b), contains(obj_list) { type = "container"; }
	Container() :Container("", false, {}, {}, "") {}
};