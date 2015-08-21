#ifndef MOC_CLIENTMANAGER_H
#define MOC_CLIENTMANAGER_H

#include "common.h"

#include <map>
#include <QtCore/QObject>
#include <QtNetwork/QTcpSocket>

class ClientConnection;

class ClientManager : public QObject {
	Q_OBJECT
public:
	ClientManager();

	u32 AddClient(QTcpSocket* clientSocket);
	u32 GetClient(QTcpSocket* clientSocket);
	void RemoveClient(QTcpSocket* clientSocket);

signals:
	void ClientAdded(u32);
	void ClientRemoved(u32);

private:
	std::map<QTcpSocket*, u32> clients;
	u32 clientIdCounter;
};

#endif//MOC_CLIENTMANAGER_H