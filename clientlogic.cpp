#include "clientlogic.h"

#include <QtGui/QLabel>

ClientLogic::ClientLogic(){
	setWindowTitle("Client");

	new QLabel("Client", this);
}

ClientLogic::~ClientLogic(){

}

