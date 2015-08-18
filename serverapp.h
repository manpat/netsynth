#ifndef SERVERAPP_H
#define SERVERAPP_H

#include <QtGui/QWidget>

class ServerApp : public QWidget {
protected:

public:
	ServerApp();
	~ServerApp();

	void Run();
};

#endif