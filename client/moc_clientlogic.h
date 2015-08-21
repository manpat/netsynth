#ifndef CLIENTLOGIC_H
#define CLIENTLOGIC_H

#include "common.h"
#include "moc_clientnetwork.h"
#include <QtCore/QObject>

class ClientGUI;
class ConnectDialog;

class ClientLogic : QObject {
	Q_OBJECT 
protected:
	ClientGUI* clientGUI;
	ConnectDialog* connectDialog;
	ClientNetwork* clientNetwork;

public:
	ClientLogic();
	~ClientLogic();

public slots:
	void requestConnect(const QString&);

	void noteChange(s8 degree, s8 octave, u8 state);
	void modeChange(Parameters paramId, bool secondary, u8 modeValue);
	void paramChange(Parameters paramId, bool secondary, f32 paramValue);
	void scaleChange(ScaleType, Notes);

signals:
	void connectResult(int);
};

#endif