#ifndef APP_H
#define APP_H

#ifdef SERVER
#	include "serverapp.h"
	using App = ServerApp;

#else
#	include "clientapp.h"
	using App = ClientApp;

#endif

#endif