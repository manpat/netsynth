#ifndef SCALE_H
#define SCALE_H

#include "typedefinitions.h"

struct Scale {
	u8* degrees;
	u8 count;

	void ConstructScale(Notes root, ScaleType);
	u8 GetNote(s8 degree, s8 octave);
};

#endif