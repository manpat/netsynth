#ifndef FMOD_MANAGER_H
#define FMOD_MANAGER_H

#include <QtCore/QThread>
#include <QtCore/QMutex>

#include <fmod.hpp>
#include <fmod_errors.h>

#include "common.h"

class FmodSystemRef {
	FMOD::System* system;
	QMutex& mutex;

public:
	FmodSystemRef(FMOD::System* s,QMutex& m): system(s), mutex(m) {}
	FmodSystemRef(FmodSystemRef&) = delete;
	FmodSystemRef(FmodSystemRef&& o)
		: mutex(o.mutex){

		system = o.system;
		o.system = nullptr;
	}

	~FmodSystemRef(){
		mutex.unlock();
	}

	FMOD::System* operator->(){
		return system;
	}
	FMOD::System& operator*(){
		return *system;
	}
};

class FmodManager : public QThread {
	Q_OBJECT

protected:
	FMOD::System* system;
	QMutex mutex;

	bool running = true;

protected:
	void run();

	static FMOD_RESULT F_CALLBACK GeneratorFunction(
		FMOD_DSP_STATE*, f32*, f32*, u32, 
		s32, s32*);

public:
	void kill();

	FmodSystemRef getSystem();

};

#endif