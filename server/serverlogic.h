#ifndef SERVERLOGIC_H
#define SERVERLOGIC_H

#include <QtGui/QWidget>
#include "moc_fmodmanager.h"
#include "common.h"

class InstrumentManager;

class ServerLogic : public QWidget {
protected:
	FmodManager fmodManager;
	InstrumentManager* instrumentManager;

public:
	ServerLogic();
	~ServerLogic();
};

#endif