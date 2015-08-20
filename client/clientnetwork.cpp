#include "moc_clientnetwork.h"
#include "packet.h"

#include <QtNetwork>

static inline QByteArray IntToArray(qint32 source);

ClientNetwork::ClientNetwork(QObject *parent) : QObject(parent){
	socket = new QTcpSocket(this);
}

bool ClientNetwork::connectToHost(QString host) {
	socket->connectToHost(host, 1337);
	return socket->waitForConnected();
}

bool ClientNetwork::writeData(PacketNote packet) {
	if (socket->state() == QAbstractSocket::ConnectedState) {
		QByteArray buf = (const char*)&packet;
		socket->write(IntToArray(buf.size()));
		socket->write(buf);
		return socket->waitForBytesWritten();
	} else {
		return false;
	}
}

bool ClientNetwork::writeData(PacketModeConfig packet) {
	if (socket->state() == QAbstractSocket::ConnectedState) {
		QByteArray buf = (const char*)&packet;
		socket->write(IntToArray(buf.size()));
		socket->write(buf);
		return socket->waitForBytesWritten();
	} else {
		return false;
	}
}

bool ClientNetwork::writeData(PacketParamConfig packet) {
	if (socket->state() == QAbstractSocket::ConnectedState) {
		QByteArray buf = (const char*)&packet;
		socket->write(IntToArray(buf.size()));
		socket->write(buf);
		return socket->waitForBytesWritten();
	} else {
		return false;
	}
}

bool ClientNetwork::writeData(PacketScale packet) {
	if (socket->state() == QAbstractSocket::ConnectedState) {
		QByteArray buf = (const char*)&packet;
		socket->write(IntToArray(buf.size()));
		socket->write(buf);
		return socket->waitForBytesWritten();
	} else {
		return false;
	}
}

QByteArray IntToArray(qint32 source) {
	QByteArray temp;
	QDataStream data(&temp, QIODevice::ReadWrite);
	data << source;
	return temp;
}