#ifndef OSCILLATOR_H
#define OSCILLATOR_H

#include "common.h"
#include "typedefinitions.h"

struct Oscillator {
	OscillatorWaveform waveform;	
	f32 octave = 1.0;
	f32 detune = 1.0;
	f32 pulsewidth = 0.5;

	f32 Generate(f64 phase, f32 frequency);
};

#endif