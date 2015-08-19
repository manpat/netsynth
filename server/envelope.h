#ifndef ENVELOPE_H
#define ENVELOPE_H

#include "common.h"

enum class EnvelopeType {
	DC,
	Linear, // Near instant onset, ignores everything but release
	AR, // Ignores decay and sustain
	ADSR,
};

struct NoteInfo;

struct Envelope {
	EnvelopeType type;
	union {
		float attack;
		float dc;
	};

	float decay;
	float sustain;
	float release;

	f32 Generate(f32 phase, NoteInfo& note);
};

#endif