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
	
	bool eventFilter(QObject*, QEvent*) override;

public slots:
	void requestConnect(const QString&);

signals:
	void connectResult(int);
};

#endif