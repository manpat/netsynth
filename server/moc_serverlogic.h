#ifndef SERVERLOGIC_H
#define SERVERLOGIC_H

#include <QtGui/QWidget>
#include "common.h"
#include "scale.h"
#include "moc_fmodmanager.h"

class InstrumentManager;

class ServerLogic : public QWidget {
	Q_OBJECT
protected:
	FmodManager fmodManager;
	InstrumentManager* instrumentManager;
	
public:
	static Scale scale;
	static f32 tempo;

public:
	ServerLogic();
	~ServerLogic();

private slots:
	void fmodready();
};

#endif