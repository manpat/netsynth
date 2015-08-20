#include "scale.h"

void Scale::ConstructScale(Notes nroot, ScaleType type){
	auto root = (u8)nroot;

	switch(type){
		case ScaleType::Major:
		case ScaleType::Minor:
			count = 7;
			break;

		case ScaleType::Pentatonic:
			count = 5;
			break;

		default: throw "Invalid scale";
	}

	if(degrees) delete[] degrees;
	degrees = new u8[count];
	u8 i = 0;

	switch(type){
		case ScaleType::Major:
			degrees[i++] = root; root += 2; // T
			degrees[i++] = root; root += 2; // T
			degrees[i++] = root; root += 1; // S
			degrees[i++] = root; root += 2; // T
			degrees[i++] = root; root += 2; // T
			degrees[i++] = root; root += 2; // T
			degrees[i++] = root; root += 1; // S
			break;
		case ScaleType::Minor:
			degrees[i++] = root; root += 2; // T
			degrees[i++] = root; root += 1; // S
			degrees[i++] = root; root += 2; // T
			degrees[i++] = root; root += 2; // T
			degrees[i++] = root; root += 1; // S
			degrees[i++] = root; root += 2; // T
			degrees[i++] = root; root += 2; // T
			break;
		case ScaleType::Pentatonic:
			degrees[i++] = root; root += 3; // 3
			degrees[i++] = root; root += 2; // T
			degrees[i++] = root; root += 2; // T
			degrees[i++] = root; root += 3; // 3
			degrees[i++] = root; root += 2; // T
			break;

		case ScaleType::Count: throw "Invalid Scale";
	}
}

u8 Scale::GetNote(s8 degree, s8 octave){
	if(!degrees) throw "GetNote on uninitialised scale";

	while(degree < 0){
		degree += count;
		--octave;
	}
	while(degree >= count){
		degree -= count;
		++octave;
	}

	return degrees[degree] + octave*12;
}