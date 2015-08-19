#include "clientlogic.h"

#include <QtGui/QLabel>
#include "moc_clientgui.h"

ClientLogic::ClientLogic(){
	clientGUI = new ClientGUI();
	clientGUI->setWindowTitle("Client");
	clientGUI->resize(800, 600);
	clientGUI->show();
}

ClientLogic::~ClientLogic(){

}

