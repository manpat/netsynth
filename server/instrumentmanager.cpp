#include "instrumentmanager.h"
#include "instrument.h"
#include "notescheduler.h"
#include "moc_fmodmanager.h"

Instrument* InstrumentManager::NewInstrument(u32 id){
	auto it = clientInstruments.find(id);
	if(it != clientInstruments.end()){
		throw "Instrument already created for userid";
	}

	auto inst = new Instrument{};
	memset(inst, 0, sizeof(Instrument));

	auto fmod = fmodManager->getSystem();

	///// BEGIN DSP
	// One of these per instrument
	FMOD_DSP_DESCRIPTION desc;
	memset(&desc, 0, sizeof(desc));

	desc.numinputbuffers = 0;
	desc.numoutputbuffers = 1;
	desc.read = GeneratorFunction;
	desc.userdata = inst;

	cfmod(fmod->createDSP(&desc, &inst->dsp));
	cfmod(inst->dsp->setChannelFormat(FMOD_CHANNELMASK_MONO, 1, FMOD_SPEAKERMODE_MONO));

	cfmod(fmod->playDSP(inst->dsp, fmodManager->getMasterChannelGroup(), false, &inst->channel));

	cfmod(fmod->createDSPByType(FMOD_DSP_TYPE_SFXREVERB, &inst->reverb));
	inst->reverb->setParameterFloat(FMOD_DSP_SFXREVERB_DRYLEVEL, -80.0);
	inst->reverb->setParameterFloat(FMOD_DSP_SFXREVERB_WETLEVEL, 0.0);
	cfmod(inst->channel->addDSP(0, inst->reverb));
	////// END DSP

	inst->scheduler = new NoteScheduler();
	inst->envelopes[0].id = 0;
	inst->envelopes[1].id = 1;

	inst->volume = 1;

	inst->oscillators[0].waveform = OscillatorWaveform::Sine;
	inst->oscillators[0].octave = 1.0;
	inst->oscillators[0].detune = 1.0;
	inst->oscillators[1].octave = 1.0;
	inst->oscillators[1].detune = 1.0;
	inst->envelopes[0].type = EnvelopeType::ADSR;
	inst->envelopes[0].attack = 0.1;
	inst->envelopes[0].decay = 0.2;
	inst->envelopes[0].sustain = 0.7;
	inst->envelopes[0].release = 0.7;

	inst->envelopes[1].type = EnvelopeType::ADSR;
	inst->envelopes[1].attack = 0.1;
	inst->envelopes[1].decay = 0.2;
	inst->envelopes[1].sustain = 0.7;
	inst->envelopes[1].release = 0.7;

	clientInstruments[id] = inst;
	return inst;
}

Instrument* InstrumentManager::GetInstrument(u32 id){
	auto it = clientInstruments.find(id);
	if (it == clientInstruments.end()) {
		// throw "GetInstrument error: Instrument doesn't exist";
		return nullptr;
	}

	return it->second;
}

void InstrumentManager::DestroyInstrument(u32 id){
	auto it = clientInstruments.find(id);
	if(it == clientInstruments.end()){
		return;
	}

	delete it->second;
	clientInstruments.erase(it);
}

void InstrumentManager::ForEachInstrument(std::function<void(Instrument&)> func){
	for(auto& p: clientInstruments){
		func(*p.second);
	}
}

FMOD_RESULT F_CALLBACK InstrumentManager::GeneratorFunction(
	FMOD_DSP_STATE* state, f32*, f32* outbuffer, u32 length, s32, s32*){

	s32 samplerate = 0;
	cfmod(state->callbacks->getsamplerate(state, &samplerate));
	f64 inc = 1.0/samplerate;

	FMOD::DSP *thisdsp = (FMOD::DSP *)state->instance; 

	void* ud = nullptr;
	cfmod(thisdsp->getUserData(&ud));
	auto& inst = *static_cast<Instrument*>(ud);

	for(u32 i = 0; i < length; ++i){
		outbuffer[i] = inst.Generate(inc);
	}

	return FMOD_OK;
}