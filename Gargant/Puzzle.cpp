#include "stdafx.h"
#pragma once

bool Puzzle::check_prereq(Game_Data& state) {
	if (prereq.size() == 0) return true;
	for (auto el : prereq) {
		if (find(state.flags_obtained.begin(), state.flags_obtained.end(), el) == state.flags_obtained.end()) return false;
	}
	return true;
}

bool Puzzle::solve(Game_Data& state, Object& u, Object& uo) {
	if (is_solved()) return false;
	else if (match(u, uo) && check_prereq(state)) {
		return solved = true;
	}
	else
		return false;
}