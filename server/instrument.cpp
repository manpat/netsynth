#include "instrument.h"
#include "notescheduler.h"
#include "typedefinitions.h"
#include <cmath>
#include <QtCore/QDebug>

Instrument::~Instrument(){
	if(scheduler){
		delete scheduler;
		scheduler = nullptr;
	}

	if(channel){
		channel->stop();
		channel = nullptr;
	}
	if(reverb){
		reverb->release();
		reverb = nullptr;
	}
	if(dsp){
		dsp->release();
		dsp = nullptr;
	}
}

// Returns frequency of note offset from A
f64 ntof(u8 n){
	f64 offset = 0.0;

	if(n & 1<<6u) {
		offset = -12.0 + 0.333;
	}else if(n & 1<<7u) {
		offset = 12.0 - 0.333;
	}

	n &= ~(3<<6u);

	return 220.0 * std::pow(2.0, ((s32)n-(s32)Notes::A + offset)/12.0);
}

f32 Instrument::Generate(f64 dt){
	if (!scheduler) {
		return 0.0f;
	}
	scheduler->Update(phase);
	
	f32 amp = 0.f;
	f32 o = 0.0;
	scheduler->ForEachActive([&](NoteInfo& ni){
		auto freq = ntof(ni.note);
		auto env1 = envelopes[0].Generate(phase, ni);
		auto env2 = envelopes[1].Generate(phase, ni);

		amp += env1 + env2;

		o += oscillators[0].Generate(phase, freq) * env1;
		o += oscillators[1].Generate(phase, freq) * env2;
	});

	phase += dt;

	currentAmplitude = amp * volume * 0.5;
	o *= 0.5 * volume;
	return o;

}

void Instrument::SetParameter(Parameters p, u8 v, bool s){
	switch(p){
	case Parameters::Waveform:
		oscillators[s?1:0].waveform = (OscillatorWaveform)v;
		break;
	case Parameters::EnvelopeType:
		envelopes[s?1:0].type = (EnvelopeType)v;
		break;
	case Parameters::Quantisation:
		scheduler->quantisation = (QuantisationSetting)v;
		scheduler->SoftClear();
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

	case Parameters::Volume:
		volume = v;
		break;
	case Parameters::Reverb:
		reverb->setParameterFloat(FMOD_DSP_SFXREVERB_DECAYTIME, v);
		// reverb->setParameterFloat(FMOD_DSP_SFXREVERB_EARLYLATEMIX, 100.0);
		break;

	default:
		return;
	}
}