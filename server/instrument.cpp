#include "instrument.h"
#include "notescheduler.h"

Instrument::~Instrument(){
	if(noteScheduler){
		delete noteScheduler;
		noteScheduler = nullptr;
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

f32 Instrument::Generate(f64 dt){
	f32 o = 0.0;
	static NoteInfo info{0.0, -1.0, 1, 0x3};
	o += oscillators[0].Generate(phase, 220.0) * envelopes[0].Generate(phase, info);
	o += oscillators[1].Generate(phase, 220.0*3.0/2.0) * envelopes[1].Generate(phase, info);
	phase += dt;
	return o * 0.5;
}