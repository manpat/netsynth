#ifndef FMOD_MANAGER_H
#define FMOD_MANAGER_H

#include <iostream>

#include <QtCore/QThread>
#include <QtCore/QMutex>

#include <fmod.hpp>
#include <fmod_errors.h>

#include "common.h"

void cfmod(FMOD_RESULT result);

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

	bool running = false;

protected:
	void run();

public:
	void kill();

	FmodSystemRef getSystem();
	bool isRunning() const {return running;};

signals:
	void ready();

};

#endif