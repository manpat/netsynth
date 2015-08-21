#include "moc_clientlogic.h"

#include <QtCore/QDebug>
#include <QtGui/QApplication>
#include <QtNetwork/QHostAddress>

#include "moc_clientgui.h"
#include "moc_connectdialog.h"
#include "moc_clientnetwork.h"
#include "packet.h"

ClientLogic::ClientLogic(){
	clientGUI = new ClientGUI();
	clientGUI->setWindowTitle("Client");
	clientGUI->resize(800, 400);
	clientGUI->show();

	clientNetwork = new ClientNetwork();
	
	auto connectDialog = new ConnectDialog(clientGUI);
	connect(connectDialog, SIGNAL(rejected()), qApp, SLOT(quit()));
	connect(connectDialog, SIGNAL(requestConnect(const QString&)), 
		this, SLOT(requestConnect(const QString&)));

	connect(this, SIGNAL(connectResult(int)), 
		connectDialog, SLOT(connectResult(int)),
		Qt::QueuedConnection);

	connectDialog->setModal(true);
	// connectDialog->show();
}

ClientLogic::~ClientLogic(){
	clientNetwork->disconnect();
	clientNetwork->deleteLater();
}

void ClientLogic::requestConnect(const QString& ip){
	if(ip.isNull()){
		emit connectResult(1);
	}else{
		qDebug() << "IP accepted";

		if(clientNetwork->connectToHost(ip)){
			qDebug() << "Connected";
			emit connectResult(0);
		}else{
			qDebug() << "Failed";
			emit connectResult(2);
		}
	}
}