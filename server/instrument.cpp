#include "instrument.h"
#include "notescheduler.h"
#include <cmath>

Instrument::~Instrument(){
	if(scheduler){
		delete scheduler;
		scheduler = nullptr;
	}

	if(channel){
		channel->stop();
		channel = nullptr;
	}
	if(dsp){
		dsp->release();
		dsp = nullptr;
	}
}

// Returns frequency of note offset from A
f32 ntof(u8 n){
	return 220.f * std::pow(2.f, ((s32)n-128)/12.f);
}

f32 Instrument::Generate(f64 dt){
	scheduler->Update(phase);
	
	f32 o = 0.0;
	// static NoteInfo info{0.0, -1.0, 1, 0x3};
	scheduler->ForEachActive([&](NoteInfo& ni){
		auto freq = ntof(ni.note);

		o += oscillators[0].Generate(phase, freq) * envelopes[0].Generate(phase, ni);
		o += oscillators[1].Generate(phase, freq) * envelopes[1].Generate(phase, ni);	
	});

	phase += dt;
	return o * 0.5;
}