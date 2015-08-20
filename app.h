#ifndef APP_H
#define APP_H

#ifdef SERVER
#	include "moc_serverlogic.h"
	using App = ServerLogic;

#else
#	include "moc_clientlogic.h"
	using App = ClientLogic;

#endif

#endif