#pragma once
struct Game_Data {
	std::vector<Event> events;
	std::vector<Room*> game_map;
	std::vector<Object> inventory;
	std::vector<Action> action_list;
	std::vector<Flag> flags_obtained;
	std::vector<Puzzle> puzzles;
	std::vector<std::string> word_pairs = { "pick up", "put down", "locked room", "wooden door", "secure door", "gold key"};
	Room *current;
	Object* focus;
	int quit = 0;
	void add_object(Object obj);
	void add_action(Action a);
	void init();
	int transfer(std::vector<Object>&, std::vector<Object>&, Object);
	Game_Data() { init();  }
	std::vector<Object>object_list(){ return current->get_objects(); }
	void make_dict();
	std::map<std::string, std::string> dict;
	void add_verb(std::string, int);
	Event& add_event(std::string s, std::vector<Flag> req, Room& r);
	Event& add_event(std::string s, std::vector<Flag> req);
	void add_puzzle(std::string name, Object use, Object used_on, Flag flag);
	void add_puzzle(std::string name, Object use, Object used_on, Flag flag, std::vector<Flag> prereq);
	void add_puzzle(std::string name, Object use, Object used_on, Flag flag, Room* lock, std::vector<Flag> prereq);
	void add_puzzle(std::string name, Object use, Object used_on, Flag flag, Room* lock);
	void connect_rooms(int, Room&, Room&, std::string, std::string from_name="");
	void Game_Data::connect_rooms(int id, Room& to, Room& from, std::string to_name, std::string from_name, std::vector<Flag*> door_lock);

	bool is_locked(Door d);
	void lock_door(Door&, std::vector<Flag*>);
};
int member_of(std::string word, std::vector<std::string> list);
Object member_of(std::string word, std::vector<Object> obj_list);
Room* member_of(std::string word, std::vector<Room*> obj_list);
std::string format(std::string);