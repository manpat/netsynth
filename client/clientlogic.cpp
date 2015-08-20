#include "moc_clientlogic.h"

#include <QtCore/QDebug>
#include <QtGui/QKeyEvent>
#include <QtGui/QApplication>
#include <QtNetwork/QHostAddress>

#include "moc_clientgui.h"
#include "moc_connectdialog.h"

ClientLogic::ClientLogic(){
	clientGUI = new ClientGUI();
	clientGUI->setWindowTitle("Client");
	clientGUI->resize(800, 400);
	clientGUI->show();

	clientGUI->installEventFilter(this);

	auto connectDialog = new ConnectDialog(clientGUI);
	connect(connectDialog, SIGNAL(rejected()), qApp, SLOT(quit()));
	connect(connectDialog, SIGNAL(requestConnect(const QString&)), 
		this, SLOT(requestConnect(const QString&)));

	connect(this, SIGNAL(connectResult(int)), 
		connectDialog, SLOT(connectResult(int)),
		Qt::QueuedConnection);

	// connectDialog->setModal(true);
	// connectDialog->show();
}

ClientLogic::~ClientLogic(){

}

bool ClientLogic::eventFilter(QObject* object, QEvent* event){
	if(event->type() == QEvent::KeyPress){
		auto keyevent = static_cast<QKeyEvent*>(event);
		if(keyevent->isAutoRepeat()) return false;

		// qDebug() << "Keypress" << keyevent->text();

	}else if(event->type() == QEvent::KeyRelease){
		auto keyevent = static_cast<QKeyEvent*>(event);
		if(keyevent->isAutoRepeat()) return false;

		// qDebug() << "Keyrelease" << keyevent->text();
	}else{
		return false;
	}

	return true;
}

void ClientLogic::requestConnect(const QString& ip){
	QHostAddress addr(ip);

	if(addr.isNull()){
		emit connectResult(1);
	}else{
		qDebug() << "IP accepted";
		// Connect here yo
		emit connectResult(0);
	}
}