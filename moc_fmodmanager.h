#ifndef FMOD_MANAGER_H
#define FMOD_MANAGER_H

#include <QtCore/QThread>

#include <fmod.hpp>
#include <fmod_errors.h>

#include "common.h"

class FmodManager : public QThread {
	Q_OBJECT

protected:
	FMOD::System* system;
	bool running = true;

protected:
	void run();

public:
	void kill();

};

#endif