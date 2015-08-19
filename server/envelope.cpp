#include "envelope.h"
#include <algorithm>
#include <cmath>

f32 Envelope::Generate(f32 phase, NoteInfo& note){
	auto position = phase /*- note.time */;

	switch(type){
		case EnvelopeType::DC: return dc;
		case EnvelopeType::Linear: return std::max(1.0-position/release, 0.0);
		case EnvelopeType::AR: 
			return std::min((position < attack)?(position/attack):(1.0-(position-attack)/release), 1.0);

		case EnvelopeType::ADSR:{
			throw "Not implemented";
			return 0.0;
		}
	}

	return 1.0; // No envelope
}
