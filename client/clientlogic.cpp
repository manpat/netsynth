#include "moc_clientlogic.h"

#include <QtCore/QDebug>
#include <QtGui/QKeyEvent>
#include <QtGui/QApplication>

#include "moc_clientgui.h"
#include "moc_connectdialog.h"

ClientLogic::ClientLogic(){
	clientGUI = new ClientGUI();
	clientGUI->setWindowTitle("Client");
	clientGUI->resize(800, 600);
	clientGUI->show();

	clientGUI->installEventFilter(this);

	auto connectdialog = new ConnectDialog(clientGUI);
	connect(connectdialog, SIGNAL(rejected()), qApp, SLOT(quit()));
	connect(connectdialog, SIGNAL(requestConnect(const QString&)), 
		this, SLOT(requestConnect(const QString&)));

	connectdialog->setModal(true);
	connectdialog->show();
}

ClientLogic::~ClientLogic(){

}

bool ClientLogic::eventFilter(QObject* object, QEvent* event){
	if(event->type() == QEvent::KeyPress){
		auto keyevent = static_cast<QKeyEvent*>(event);
		if(keyevent->isAutoRepeat()) return false;

		qDebug() << "Keypress" << keyevent->text();

	}else if(event->type() == QEvent::KeyRelease){
		auto keyevent = static_cast<QKeyEvent*>(event);
		if(keyevent->isAutoRepeat()) return false;

		qDebug() << "Keyrelease" << keyevent->text();
	}else{
		return false;
	}

	return true;
}

void ClientLogic::requestConnect(const QString& ip){
	qDebug() << "Request connect to" << ip;
}