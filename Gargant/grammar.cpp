#include "stdafx.h"
#pragma once

void Parser::init() {
	pos_list = {
		BEGIN,
		NOUN,
		PLURAL,
		NOUN_PHRASE,
		VERB_PARTICIPLE,
		VERB_TRANSITIVE,
		VERB_INTRANSITIVE,
		ADJ,
		ADV,
		CONJUNCTION,
		PREPOSITION,
		INTERJECTION,
		PRONOUN,
		DEFINITE_ARTICLE,
		INDEFINITE_ARTICLE,
		NOMINATIVE,
		END,
		ROOM,
		DOOR
	};
	for (auto el : pos_list) {
		Parse_Node tmp(el);
		node_graph.push_back(tmp);
	}
	directed_edge(BEGIN, PRONOUN);
	directed_edge(BEGIN, DEFINITE_ARTICLE);
	directed_edge(BEGIN, INDEFINITE_ARTICLE);
	directed_edge(BEGIN, ADV);
	directed_edge(BEGIN, VERB_TRANSITIVE);
	directed_edge(BEGIN, VERB_INTRANSITIVE);
	directed_edge(BEGIN, VERB_PARTICIPLE);

	directed_edge(PRONOUN, VERB_INTRANSITIVE);
	directed_edge(PRONOUN, VERB_TRANSITIVE);

	directed_edge(VERB_TRANSITIVE, NOUN);
	directed_edge(VERB_TRANSITIVE, ROOM);
	directed_edge(VERB_TRANSITIVE, DOOR);
	directed_edge(VERB_TRANSITIVE, INDEFINITE_ARTICLE);
	directed_edge(VERB_TRANSITIVE, DEFINITE_ARTICLE);
	directed_edge(VERB_TRANSITIVE, PREPOSITION);
	directed_edge(VERB_TRANSITIVE, ADJ);
	directed_edge(VERB_TRANSITIVE, END);

	directed_edge(VERB_INTRANSITIVE, END);

	directed_edge(PREPOSITION, DEFINITE_ARTICLE);
	directed_edge(PREPOSITION, NOUN);
	directed_edge(PREPOSITION, ADJ);
	directed_edge(PREPOSITION, ROOM);
	directed_edge(PREPOSITION, DOOR);

	directed_edge(INDEFINITE_ARTICLE, ADJ);
	directed_edge(INDEFINITE_ARTICLE, NOUN);
	directed_edge(INDEFINITE_ARTICLE, ROOM);
	directed_edge(INDEFINITE_ARTICLE, DOOR);

	directed_edge(DEFINITE_ARTICLE, ADJ);
	directed_edge(DEFINITE_ARTICLE, NOUN);
	directed_edge(DEFINITE_ARTICLE, ROOM);
	directed_edge(DEFINITE_ARTICLE, DOOR);

	directed_edge(ADJ, ADJ);
	directed_edge(ADJ, NOUN);
	directed_edge(ADJ, DOOR);

	directed_edge(ROOM, END);

	directed_edge(DOOR, END);

	directed_edge(NOUN, NOUN);
	directed_edge(NOUN, PREPOSITION);
	directed_edge(NOUN, END);
}