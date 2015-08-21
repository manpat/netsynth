#ifndef INSTRUMENTMANAGER_H
#define INSTRUMENTMANAGER_H

#include "common.h"
#include <map>
#include <functional>

#include <fmod.hpp>

struct Instrument;
class FmodManager;

struct InstrumentManager {
	FmodManager* fmodManager;
	std::map<u32, Instrument*> clientInstruments;

	Instrument* NewInstrument(u32);
	Instrument* GetInstrument(u32);
	void DestroyInstrument(u32);

	void ForEachInstrument(std::function<void(Instrument&)>);

private:
	static FMOD_RESULT F_CALLBACK GeneratorFunction(
		FMOD_DSP_STATE*, f32*, f32*, u32, 
		s32, s32*);
};

#endif