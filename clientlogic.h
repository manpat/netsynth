#ifndef CLIENTLOGIC_H
#define CLIENTLOGIC_H

#include "common.h"

class ClientGUI;

class ClientLogic {
protected:
	ClientGUI* clientGUI;

public:
	ClientLogic();
	~ClientLogic();
};

#endif