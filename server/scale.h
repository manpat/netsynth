#ifndef SCALE_H
#define SCALE_H

#include "common.h"

enum class ScaleType {
	Major,
	Minor,
	Pentatonic,
	// Blues
	// Modes
};

enum class Notes : u8 {
	A = 128, As, B, C, Cs, 
	D, Ds, E, F, Fs, G, Gs
};

struct Scale {
	u8* degrees;
	u8 count;

	void ConstructScale(Notes root, ScaleType);
	u8 GetNote(s8 degree, s8 octave);
};

#endif