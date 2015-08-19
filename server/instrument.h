#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include "common.h"
#include "oscillator.h"
#include "envelope.h"

struct Instrument {
	Oscillator oscillators[2];
	Envelope envelopes[2];
	f64 phase = 0;

	f32 Generate(f64 dt);
};

#endif