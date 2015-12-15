#include "moc_servernetwork.h"

#include "instrumentmanager.h"
#include "packet.h"
#include <iostream>

static inline qint32 ArrayToInt(QByteArray source);

ServerNetwork::ServerNetwork(QObject *parent) : QObject(parent) {
	clientManager = new ClientManager();

	server = new QTcpServer(this);
	connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));
	server->listen(QHostAddress::Any, 1337);

	for(auto i : QNetworkInterface::allAddresses()) {
		if (i.protocol() == QAbstractSocket::IPv4Protocol && i != QHostAddress(QHostAddress::LocalHost))
			// if(i.toString().contains("192.168") || i.toString().contains("10.") || i.toString().contains("172"))
			qDebug() << "Listening on:" << qPrintable(i.toString());
	}
}

void ServerNetwork::newConnection() {
	while (server->hasPendingConnections()) {
		QTcpSocket *socket = server->nextPendingConnection();
		s32 clientId = clientManager->AddClient(socket);

		emit ClientConnect(clientId);

		connect(socket, SIGNAL(readyRead()), SLOT(readyRead()));
		connect(socket, SIGNAL(disconnected()), SLOT(disconnected()));

		QByteArray *buffer = new QByteArray();
		buffers.insert(socket, buffer);

		qDebug().nospace() << "Connected:    Instrument #" << clientId << " at " << qPrintable(socket->peerAddress().toString()) << ":" << socket->peerPort();
	}
}

void ServerNetwork::disconnected() {
	QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
	QByteArray *buffer = buffers.value(socket);
	auto clientId = clientManager->GetClient(socket);

	emit ClientDisconnect(clientId);

	qDebug().nospace() << "Disconnected: Instrument #" << clientId << " at " << qPrintable(socket->peerAddress().toString()) << ":" << socket->peerPort();

	clientManager->RemoveClient(socket);
	socket->deleteLater();
	delete buffer;
}

void ServerNetwork::readyRead() {
	QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
	u32 clientId = clientManager->GetClient(socket);
	QByteArray *buffer = buffers.value(socket);
	qint32 size = socket->bytesAvailable();

	while (socket->bytesAvailable() > 0) {
		buffer->append(socket->readAll());

		while ((size == 0 && buffer->size() >= 4) || (size > 0 && buffer->size() >= size)) {
			if (size == 0 && buffer->size() >= 4) {
				size = ArrayToInt(buffer->mid(0, 4));
				buffer->remove(0, 4);
			}
			if (size > 0 && buffer->size() >= size) {
				QByteArray data = buffer->mid(0, size);
				buffer->remove(0, size);
				size = 0;

				emit DataReceived(data, clientId);
			}
		}
	}
}

qint32 ArrayToInt(QByteArray source) {
	qint32 temp;
	QDataStream data(&source, QIODevice::ReadWrite);
	data >> temp;
	return temp;
}