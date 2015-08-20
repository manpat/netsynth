#ifndef ENVELOPE_H
#define ENVELOPE_H

#include "common.h"
#include "typedefinitions.h"

struct NoteInfo;

struct Envelope {
	EnvelopeType type;
	u8 id;
	
	union {
		f32 attack;
		f32 dc;
	};

	f32 decay;
	f32 sustain;
	f32 release;

	f32 Generate(f32 phase, NoteInfo& note);
};

#endif