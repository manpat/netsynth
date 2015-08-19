#ifndef ENVELOPE_H
#define ENVELOPE_H

#include "common.h"

enum class EnvelopeType : u8 {
	None = 0,
	DC,
	Linear, // Near instant onset, ignores everything but release
	AR, // Ignores decay and sustain
	ADSR,
};

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