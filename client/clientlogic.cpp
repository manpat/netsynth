#include "moc_clientlogic.h"

#include <QtCore/QDebug>
#include <QtGui/QKeyEvent>
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

	clientGUI->installEventFilter(this);

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

bool ClientLogic::eventFilter(QObject* object, QEvent* event){
	if(event->type() == QEvent::KeyPress){
		auto keyevent = static_cast<QKeyEvent*>(event);
		if(keyevent->isAutoRepeat()) return false;

		PacketNote packetNote;

		packetNote.degree = 2;
		packetNote.octave = 0;
		packetNote.state = 1;

		clientNetwork->writeData(packetNote);

	}else if(event->type() == QEvent::KeyRelease){
		auto keyevent = static_cast<QKeyEvent*>(event);
		if(keyevent->isAutoRepeat()) return false;

		PacketNote packetNote;

		packetNote.degree = 2;
		packetNote.octave = 0;
		packetNote.state = 0;

		clientNetwork->writeData(packetNote);
	}else{
		return false;
	}

	return true;
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