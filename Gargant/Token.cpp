#include "stdafx.h"
#pragma once

void advance_state(Token& tok) { ++tok.state; }
void advance_state(Container& cont) { (cont.is_open() ? --cont.state : ++cont.state); }

int generate_id() {
	static int id_ref = 0;
	return id_ref;
}

bool operator== (const Token& lhs, const Token& rhs) {
	return lhs.name == rhs.name;
}
