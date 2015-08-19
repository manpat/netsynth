#include "moc_fmodmanager.h"
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
	mutex.unlock();

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