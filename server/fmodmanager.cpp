#include "moc_fmodmanager.h"
#include <iostream>
#include <cmath>

static void cfmod(FMOD_RESULT result) {
	if (result != FMOD_OK) {
		std::cerr << "FMOD error! (" << result << ") " << FMOD_ErrorString(result) << std::endl;
		throw "FMOD Error";
	}
}

void FmodManager::run(){
	cfmod(FMOD::System_Create(&system));

	u32 version = 0;
	cfmod(system->getVersion(&version));
	if(version < FMOD_VERSION){
		std::cerr 
			<< "FMOD version of at least " << FMOD_VERSION 
			<< " required. Version used " << version 
			<< std::endl;
		throw "FMOD Error";
	}

	cfmod(system->init(100, FMOD_INIT_NORMAL, nullptr));

	///// BEGIN DSP
	// One of these per instrument, maybe
	FMOD_DSP_DESCRIPTION desc;
	memset(&desc, 0, sizeof(desc));

	desc.numinputbuffers = 0;
	desc.numoutputbuffers = 1;
	desc.read = GeneratorFunction;
	desc.userdata = new double;

	FMOD::DSP* dsp; // This goes in an instrument (maybe)
	FMOD::Channel* channel; // This goes in an instrument (definitely)
	cfmod(system->createDSP(&desc, &dsp));
	cfmod(dsp->setChannelFormat(FMOD_CHANNELMASK_MONO,1,FMOD_SPEAKERMODE_MONO));

	cfmod(system->playDSP(dsp, nullptr /*channel group*/, false, &channel));
	////// END DSP

	running = true;
	while(running){
		mutex.lock();
		cfmod(system->update());
		mutex.unlock();
		msleep(30);
	}

	std::cout << "FmodManager stopped" << std::endl;
	emit finished();
}

void FmodManager::kill(){
	running = false;
}

FmodSystemRef FmodManager::getSystem(){
	mutex.lock();
	return FmodSystemRef{system, mutex};
}

FMOD_RESULT F_CALLBACK FmodManager::GeneratorFunction(
	FMOD_DSP_STATE* state, f32*, f32* outbuffer, u32 length, s32, s32*){

	s32 samplerate = 0;
	cfmod(state->callbacks->getsamplerate(state, &samplerate));
	f64 inc = 1.0/samplerate;

	FMOD::DSP *thisdsp = (FMOD::DSP *)state->instance; 

	void* ud = nullptr;
	cfmod(thisdsp->getUserData(&ud));
	auto& phase = *static_cast<double*>(ud);

	for(u32 i = 0; i < length; ++i){
		outbuffer[i] = sin(phase*M_PI*2.0* 88.0) * std::min(std::log(phase*0.1 + 1.0), 1.0);
		phase += inc;
	}

	return FMOD_OK;
}