#ifndef OSCILLATOR_H
#define OSCILLATOR_H

#include "common.h"

enum class OscillatorWaveform {
	Sine, Square, Triangle, Saw,
};

struct Oscillator {
	OscillatorWaveform waveform;	
	f32 detune = 0.0;
	f32 pulsewidth = 0.5;

	f32 Generate(f64 phase, f32 frequency);
};

#endif