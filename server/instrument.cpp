#include "instrument.h"
#include "notescheduler.h"
#include "typedefinitions.h"
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
f64 ntof(u8 n){
	return 220.0 * std::pow(2.0, ((s32)n-128)/12.0);
}

f32 Instrument::Generate(f64 dt){
	scheduler->Update(phase);
	
	f32 o = 0.0;
	scheduler->ForEachActive([&](NoteInfo& ni){
		auto freq = ntof(ni.note);

		o += oscillators[0].Generate(phase, freq) * envelopes[0].Generate(phase, ni);
		o += oscillators[1].Generate(phase, freq) * envelopes[1].Generate(phase, ni);	
	});

	phase += dt;
	return o * 0.5;
}

void Instrument::SetParameter(Parameters p, u8 v, bool s){
	switch(p){
	case Parameters::Waveform:
		oscillators[s?1:0].waveform = (OscillatorWaveform)v;
		break;
	case Parameters::EnvelopeType:
		envelopes[s?1:0].type = (EnvelopeType)v;
		break;

	default:
		return;
	}
}
void Instrument::SetParameter(Parameters p, f32 v, bool s){
	switch(p){
	case Parameters::OctaveShift:
		oscillators[s?1:0].octave = v;
		break;
	case Parameters::Detune:
		oscillators[s?1:0].detune = v;
		break;
	case Parameters::PulseWidth:
		oscillators[s?1:0].pulsewidth = v;
		break;

	case Parameters::Attack:
		envelopes[s?1:0].attack = v;
		break;
	case Parameters::Decay:
		envelopes[s?1:0].decay = v;
		break;
	case Parameters::Sustain:
		envelopes[s?1:0].sustain = v;
		break;
	case Parameters::Release:
		envelopes[s?1:0].release = v;
		break;

	default:
		return;
	}
}