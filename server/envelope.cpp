#include <algorithm>
#include <cmath>

#include "envelope.h"
#include "notescheduler.h"

f32 Envelope::Generate(f32 phase, NoteInfo& note){
	if(!(note.envFlags & (1<<id))) return 0.0;
	 
	auto position = phase - note.beginTime;

	switch(type){
		case EnvelopeType::None: 
			note.envFlags &= ~(1<<id); 
			return 0.0;

		case EnvelopeType::DC: {
			if(!note.held()) note.envFlags &= ~(1<<id);
			return dc;
		}
		case EnvelopeType::Linear: {
			auto o = 1.0-position/release;
			if(o < 0.0) note.envFlags &= ~(1<<id);

			return std::max(o, 0.0);
		}
		case EnvelopeType::AR: {
			auto o = (position < attack)?(position/attack):(1.0-(position-attack)/release);
			if(o < 0.0) note.envFlags &= ~(1<<id);

			return std::min(o, 1.0);
		}

		case EnvelopeType::ADSR:{
			throw "Not implemented";
			return 0.0;
		}
	}

	return 1.0; // No envelope
}
