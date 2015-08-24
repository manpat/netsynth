#ifndef TYPEDEFINITIONS_H
#define TYPEDEFINITIONS_H

#include "common.h"

enum class EnvelopeType : u8 {
	None = 0,
	DC,
	Linear, // Near instant onset, ignores everything but release
	AR, // Ignores decay and sustain
	ADSR,
	Count,
};

enum class OscillatorWaveform : u8 {
	None = 0, Sine, Square, Triangle, Saw,
	Count,
};

enum class ScaleType : u8 {
	Major,
	Minor,
	Pentatonic,
	// Blues
	// Modes
	Count,
};

enum class QuantisationSetting : u8 {
	None,
	Sixteenth,
	Twelfth,
	Eighth,
	Sixth,
	Quarter,
	Triplet,
	Half,
	Whole,
	Count
};

enum class Notes : u8 {
	A = 128, As, B, C, Cs, 
	D, Ds, E, F, Fs, G, Gs,

	Count = (Gs+1)-A,
};

enum class Parameters : u8{
	// Mode
	Waveform = 0,
	EnvelopeType,

	// Inst mode
	Quantisation,

	// Param
	OctaveShift = 0, // Starting again means we get more parameters
	Detune,
	PulseWidth,
	Attack,
	Decay,
	Sustain,
	Release,

	// Inst param
	Volume,
	Reverb,

	// Server param
	Tempo,
};

struct PacketType {
	u8 packetType : 2;
	u8 secondary : 1;
	u8 param : 5;
};

#endif