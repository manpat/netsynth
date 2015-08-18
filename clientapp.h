#ifndef CLIENTAPP_H
#define CLIENTAPP_H

#include <QtGui/QWidget>

class ClientApp : public QWidget {
protected:

public:
	ClientApp();
	~ClientApp();

	void Run();
};

#endif