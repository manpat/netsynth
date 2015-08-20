#include "moc_clientnetwork.h"
#include "packet.h"

static inline QByteArray IntToArray(qint32 source);

ClientNetwork::ClientNetwork(QObject *parent) : QObject(parent){
	socket = new QTcpSocket(this);
}

bool ClientNetwork::connectToHost(QString host) {
	socket->connectToHost(host, 1337);
	return socket->waitForConnected();
}

bool ClientNetwork::writeData(const PacketNote &packet) {
	if (socket->state() == QAbstractSocket::ConnectedState) {
		auto buf = QByteArray((const char*)&packet, sizeof(packet));
		socket->write(buf);
		return socket->waitForBytesWritten();
	} else {
		return false;
	}
}

bool ClientNetwork::writeData(const PacketModeConfig &packet) {
	if (socket->state() == QAbstractSocket::ConnectedState) {
		auto buf = QByteArray((const char*)&packet, sizeof(packet));
		socket->write(buf);
		return socket->waitForBytesWritten();
	} else {
		return false;
	}
}

bool ClientNetwork::writeData(const PacketParamConfig &packet) {
	if (socket->state() == QAbstractSocket::ConnectedState) {
		auto buf = QByteArray((const char*)&packet, sizeof(packet));
		socket->write(buf);
		return socket->waitForBytesWritten();
	} else {
		return false;
	}
}

bool ClientNetwork::writeData(const PacketScale &packet) {
	if (socket->state() == QAbstractSocket::ConnectedState) {
		auto buf = QByteArray((const char*)&packet, sizeof(packet));
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