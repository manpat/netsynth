#include <algorithm>
#include <cmath>
#include <iostream>

#include "envelope.h"
#include "notescheduler.h"
#include "moc_serverlogic.h"

f32 Envelope::Generate(f32 phase, NoteInfo& note){
	if(!(note.envFlags & (1<<id))) return 0.0;
	 
	phase *= ServerLogic::tempo / 60.0;
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
			// auto diff = note.endTime - note.beginTime;
			auto rpos = phase - note.endTime;

			if(position <= attack){
				return std::min(position/attack, 1.f);

			}else if(position-attack <= decay){
				return std::max(1.0 - (position-attack)/decay *(1.0-sustain), 0.0);

			}else if(note.held() || rpos < 0){
				return sustain;

			}else if(rpos < release){
				return std::max((1.0-rpos/release)/sustain, 0.0);
				// return sustain*(1.0 + (note.endTime - phase)/(release - note.beginTime));
			}

			note.envFlags &= ~(1<<id);
			return 0.0;
		}

		default: throw "Invalid envelope";
	}

	return 0.0; // No envelope
}
