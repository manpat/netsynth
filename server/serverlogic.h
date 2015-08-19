#ifndef SERVERLOGIC_H
#define SERVERLOGIC_H

#include <QtGui/QWidget>
#include "common.h"
#include "scale.h"
#include "moc_fmodmanager.h"

class InstrumentManager;

class ServerLogic : public QWidget {
protected:
	FmodManager fmodManager;
	InstrumentManager* instrumentManager;
	Scale scale;

public:
	ServerLogic();
	~ServerLogic();
};

#endif