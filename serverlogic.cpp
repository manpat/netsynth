#include "serverlogic.h"

#include <QtGui/QLabel>

ServerLogic::ServerLogic(){
	setWindowTitle("Server");

	fmodManager.start();
}

ServerLogic::~ServerLogic(){
	fmodManager.kill();
	fmodManager.wait(2000); // Wait max 2s
	fmodManager.terminate(); // Just in case
}
