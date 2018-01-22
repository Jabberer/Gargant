#pragma once

class Binder {
public:
	Game_Data* state;
	Object* Binder::get_Object(std::vector<std::pair<std::string, std::string>>);
	Object* Binder::get_Object(std::vector<std::pair<std::string, std::string>>, std::vector<Object*>);
	Action* get_Action(std::string);
	Door* get_Door(std::string);
	Room* get_Room(std::string);
	std::string call(std::vector<std::pair<Token*,std::string>>);
	std::string bind(std::vector<std::pair<std::string, std::string>>);
	std::string pick_up(Object*);
	std::string pick_up(Door*);
	std::string put_down(Object*);
	std::string put_down(Door*);
	std::string examine();
	std::string examine(Room*);
	std::string examine(Object*);
	std::string examine(Door*);
	std::string move(Room*);
	std::string move(Door*);
	std::string use(Object*);
	std::string use(Object*, Object*);
	std::string Binder::use(Container*);
	std::string translate(Action&);
	std::string translate(Action&, Object*);
	std::string translate(Action&, Room*);
	std::string translate(Action&, Door*);
	std::string translate(Action&, Object*, Object*);
	Binder(Game_Data* d) :state(d) {}
	std::vector<Object*> Binder::pool_objects();
};