#ifndef INSTRUMENTMANAGER_H
#define INSTRUMENTMANAGER_H

#include "common.h"
#include <map>

struct Instrument;

struct InstrumentManager {
	std::map<u32, Instrument*> clientInstruments;
};

#endif