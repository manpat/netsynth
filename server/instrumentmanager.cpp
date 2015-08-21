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
	cfmod(inst->dsp->setChannelFormat(FMOD_CHANNELMASK_MONO,1,FMOD_SPEAKERMODE_MONO));

	cfmod(fmod->playDSP(inst->dsp, nullptr /*channel group*/, false, &inst->channel));
	////// END DSP

	inst->scheduler = new NoteScheduler();
	inst->envelopes[0].id = 0;
	inst->envelopes[1].id = 1;

	clientInstruments[id] = inst;
	return inst;
}

Instrument* InstrumentManager::GetInstrument(u32 id)
{
	auto it = clientInstruments.find(id);
	if (it != clientInstruments.end()) {
		return it->second;
	}
	throw "GetInstrument error: Instrument doesn't exist";
}

void InstrumentManager::DestroyInstrument(u32 id){
	auto it = clientInstruments.find(id);
	if(it == clientInstruments.end()){
		return;
	}

	delete it->second;
	clientInstruments.erase(it);
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

	static bool go = false;
	if(inst.scheduler->time > 3.1 && !go){
		go = true;
		inst.scheduler->NoteOff(128-12);
		inst.scheduler->NoteOff(128-8);
		inst.scheduler->NoteOff(128-1);
		
		inst.scheduler->quantisation = QuantisationSetting::Triplet;
		inst.scheduler->NoteOn(128+7);
		inst.scheduler->NoteOn(128+4, 0.4);
		inst.scheduler->NoteOn(128, 0.8);
		inst.scheduler->NoteOn(128-5, 1.0);
		inst.scheduler->NoteOn(128-12, 1.5);
		inst.scheduler->NoteOn(128-8, 2.0);
	}

	for(u32 i = 0; i < length; ++i){
		outbuffer[i] = inst.Generate(inc);
	}

	return FMOD_OK;
}