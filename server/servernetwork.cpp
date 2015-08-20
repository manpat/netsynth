#include "moc_servernetwork.h"
#include "packet.h"
#include <iostream>

static inline qint32 ArrayToInt(QByteArray source);

ServerNetwork::ServerNetwork(QObject *parent) : QObject(parent) {
	server = new QTcpServer(this);

	connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));
	
	server->listen(QHostAddress::Any, 1337);

	qDebug() << "Listening on port 1337";
}

void ServerNetwork::newConnection() {
	while (server->hasPendingConnections()) {
		QTcpSocket *socket = server->nextPendingConnection();
		connect(socket, SIGNAL(readyRead()), SLOT(readyRead()));
		connect(socket, SIGNAL(disconnected()), SLOT(disconnected()));

		QByteArray *buffer = new QByteArray();
		qint32 *s = new qint32(0);

		buffers.insert(socket, buffer);
		sizes.insert(socket, s);

		qDebug() << "Connected to " << socket->peerName() << " at " << socket->peerAddress() << ":" << socket->peerPort();
	}
}

void ServerNetwork::disconnected() {

	QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
	QByteArray *buffer = buffers.value(socket);
	qint32 *s = sizes.value(socket);

	qDebug() << "Disconnected from " << socket->peerName() << " at " << socket->peerAddress() << ":" << socket->peerPort();

	socket->deleteLater();
	delete buffer;
	delete s;
}

void ServerNetwork::readyRead() {
	QTcpSocket *socket = static_cast<QTcpSocket*>(sender());
	QByteArray *buffer = buffers.value(socket);
	qint32 size = *(sizes.value(socket));
	//qint32 size = *s;

	while (socket->bytesAvailable() > 0) {
		buffer->append(socket->readAll());

		for (int i = 0; i < buffer->size(); i++) {
			qDebug() << i << ":" << (int)(buffer->at(i));
		}

		while ((size == 0 && buffer->size() >= 4) || (size > 0 && buffer->size() >= size)) {
			if (size == 0 && buffer->size() >= 4) {
				size = ArrayToInt(buffer->mid(0, 4));
				buffer->remove(0, 4);
			}
			if (size > 0 && buffer->size() >= size) {
				QByteArray data = buffer->mid(0, size);
				buffer->remove(0, size);
				size = 0;

				emit dataReceived(data);
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