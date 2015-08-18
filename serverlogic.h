#ifndef SERVERLOGIC_H
#define SERVERLOGIC_H

#include <QtGui/QWidget>
#include "moc_fmodmanager.h"
#include "common.h"

class ServerLogic : public QWidget {
protected:
	FmodManager fmodManager;

public:
	ServerLogic();
	~ServerLogic();
};

#endif