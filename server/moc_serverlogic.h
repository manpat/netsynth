#ifndef SERVERLOGIC_H
#define SERVERLOGIC_H

#include <QtGui/QWidget>
#include "common.h"
#include "scale.h"
#include "moc_fmodmanager.h"
#include "moc_servernetwork.h"

class InstrumentManager;

class ServerLogic : public QWidget {
	Q_OBJECT
protected:
	FmodManager fmodManager;
	InstrumentManager* instrumentManager;
	ServerNetwork* serverNetwork;
	
public:
	static Scale scale;
	static f32 tempo;

public:
	ServerLogic();
	~ServerLogic();

private slots:
	void fmodready();
	void handleData(QByteArray data);
};

#endif