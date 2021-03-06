#ifndef SERVERLOGIC_H
#define SERVERLOGIC_H

#include <QtGui/QWidget>
#include "common.h"
#include "scale.h"
#include "moc_fmodmanager.h"
#include "moc_servernetwork.h"
#include "moc_servergui.h"

class InstrumentManager;

class ServerLogic : public QWidget {
	Q_OBJECT
protected:
	ServerGUI* serverGUI;
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
	void HandleData(QByteArray data, u32 id);
	void ClientConnected(u32 id);
	void ClientDisconnected(u32 id);
	void UpdateVisualizer();
};

#endif