#include <algorithm>
#include <cmath>
#include <iostream>

#include "envelope.h"
#include "notescheduler.h"
#include "serverlogic.h"

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
			auto rpos = phase - note.endTime;

			if(position < attack){
				return position/attack;

			}else if(position-attack < decay){
				return 1.0 - (position-attack)/decay *(1.0-sustain);

			}else if(note.held()){
				return sustain;

			}else if(rpos < release){
				return (1.0 - rpos/release)*sustain;
			}

			note.envFlags &= ~(1<<id);
			return 0.0;
		}
	}

	return 0.0; // No envelope
}
