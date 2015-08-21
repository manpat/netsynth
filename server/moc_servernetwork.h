#ifndef MOC_SERVERNETWORK_HPP
#define MOC_SERVERNETWORK_HPP

#include "common.h"
#include "moc_clientmanager.h"

#include <QtCore/QtCore>
#include <QtNetwork/QtNetwork>

class ServerNetwork : public QObject {
	Q_OBJECT
public:
	explicit ServerNetwork(QObject *parent = 0);

signals:
	void DataReceived(QByteArray, u32);

private slots:
	void newConnection();
	void disconnected();
	void readyRead();

private:
	QTcpServer *server;
	QHash<QTcpSocket*, QByteArray*> buffers;
	ClientManager* clientManager;
};

#endif//MOC_SERVERNETWORK_HPP