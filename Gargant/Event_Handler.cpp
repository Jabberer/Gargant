#include "stdafx.h"
#pragma once

std::string Event_Handler::activate(Event& e) {
	e.use();
	for (auto el : e.collect()) {
		state->inventory.push_back(el);
	}
	return e.get_txt();
}

bool Event_Handler::check_req(Event e) {
	if (e.is_used()) return false;
	if (e.get_dest().get_name() == "" || e.get_dest() == *state->current) {
		for (auto req_flag : e.get_req()) {
			bool match = false;
			for (auto check_flag : state->flags_obtained) {
				if (req_flag == check_flag)
					match = true;
			}
			if (!match) return false;
		}
		return true;
	}
	return false;
}

std::string Event_Handler::process_events() {
	for (auto &el : state->events) {
		if (check_req(el)) {
			return activate(el);
		}
	}
	return "";
}