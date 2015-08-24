#ifndef INSTRUMENT_H
#define INSTRUMENT_H

#include "common.h"
#include "oscillator.h"
#include "envelope.h"

#include <fmod.hpp>

struct NoteScheduler;

struct Instrument {
	Oscillator oscillators[2];
	Envelope envelopes[2];
	f64 phase = 0;
	f32 volume = 1;
	f32 currentAmplitude;

	FMOD::Channel* channel;
	FMOD::DSP* dsp;
	NoteScheduler* scheduler;
	
	FMOD::DSP* reverb;

	~Instrument();

	void SetParameter(Parameters, u8, bool secondary);
	void SetParameter(Parameters, f32, bool secondary);
	f32 Generate(f64 dt);
};

#endif