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
	clientGUI->setWindowTitle("NetSynth Client");
	clientGUI->resize(800, 400);
	clientGUI->show();

	clientNetwork = new ClientNetwork();

	connect(clientGUI, SIGNAL(notifyNoteChange(s8,s8,u8)), this, SLOT(noteChange(s8,s8,u8)));
	connect(clientGUI, SIGNAL(notifyModeChange(Parameters,bool,u8)),
		this, SLOT(modeChange(Parameters,bool,u8)));
	connect(clientGUI, SIGNAL(notifyParamChange(Parameters,bool,f32)),
		this, SLOT(paramChange(Parameters,bool,f32)));
	connect(clientGUI, SIGNAL(notifyScaleChange(ScaleType,Notes)),
		this, SLOT(scaleChange(ScaleType,Notes)));

	auto connectDialog = new ConnectDialog(clientGUI);
	connect(connectDialog, SIGNAL(rejected()), qApp, SLOT(quit()));
	connect(connectDialog, SIGNAL(requestConnect(const QString&)),
		this, SLOT(requestConnect(const QString&)));

	connect(this, SIGNAL(connectResult(int)),
		connectDialog, SLOT(connectResult(int)),
		Qt::QueuedConnection);

	connectDialog->setModal(true);
	connectDialog->show();
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
			clientGUI->SetDefaults();
			emit connectResult(0);
		}else{
			qDebug() << "Failed";
			emit connectResult(2);
		}
	}
}

void ClientLogic::noteChange(s8 degree, s8 octave, u8 state){
	PacketNote packet;
	packet.packetType = 0;
	packet.secondary = 0;
	packet.param = 0;

	packet.degree = degree;
	packet.octave = octave;
	packet.state = state;

	clientNetwork->writeData(packet);
}
void ClientLogic::scaleChange(ScaleType sc, Notes n){
	PacketScale packet;
	packet.packetType = 1;
	packet.secondary = 0;
	packet.param = 0;

	packet.scaleType = sc;
	packet.rootNote = n;

	clientNetwork->writeData(packet);
}
void ClientLogic::modeChange(Parameters paramId, bool secondary, u8 modeValue){
	PacketModeConfig packet;

	packet.packetType = 2;
	packet.secondary = secondary;
	packet.param = (u8)paramId;
	packet.value = modeValue;

	clientNetwork->writeData(packet);
}
void ClientLogic::paramChange(Parameters paramId, bool secondary, f32 paramValue){
	PacketParamConfig packet;

	packet.packetType = 3;
	packet.secondary = secondary;
	packet.param = (u8)paramId;
	packet.value = paramValue;

	clientNetwork->writeData(packet);

}
