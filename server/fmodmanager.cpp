#include "moc_fmodmanager.h"
#include <QtCore/QDebug>
#include <iostream>
#include <cmath>

void cfmod(FMOD_RESULT result) {
	if (result != FMOD_OK) {
		std::cerr << "FMOD error! (" << result << ") " << FMOD_ErrorString(result) << std::endl;
		throw "FMOD Error";
	}
}

void FmodManager::run(){
	running = false;
	mutex.lock();
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
	cfmod(system->createDSPByType(FMOD_DSP_TYPE_COMPRESSOR, &compressor));
	cfmod(system->getMasterChannelGroup(&mastergroup));
	
	cfmod(compressor->setParameterFloat(FMOD_DSP_COMPRESSOR_THRESHOLD, -13));
	cfmod(compressor->setParameterFloat(FMOD_DSP_COMPRESSOR_ATTACK, 0.5));
	cfmod(compressor->setBypass(false));
	cfmod(mastergroup->addDSP(0, compressor));
	
	mutex.unlock();

	emit ready();

	running = true;
	while(running){
		mutex.lock();
		cfmod(system->update());
		mutex.unlock();

		emit UpdateVisualizer();

		msleep(30);
	}

	qDebug() << "FmodManager stopped";
	emit finished();
}

void FmodManager::kill(){
	running = false;
}

FmodSystemRef FmodManager::getSystem(){
	mutex.lock();
	return FmodSystemRef{system, mutex};
}