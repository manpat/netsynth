#ifndef MOC_CLIENTNETWORK_HPP
#define MOC_CLIENTNETWORK_HPP

#include "packet.h"

#include <QtCore/QtCore>
#include <QtNetwork/QtNetwork>

class ClientNetwork : public QObject {
	Q_OBJECT
public:
	explicit ClientNetwork(QObject *parent = 0);

public slots:
	bool connectToHost(QString host);
	bool writeData(const PacketNote &packet);
	bool writeData(const PacketUserData &packet);
	bool writeData(const PacketModeConfig &packet);
	bool writeData(const PacketParamConfig &packet);
	bool writeData(const PacketScale &packet);

private:
	QTcpSocket *socket;
};

#endif//MOC_CLIENTNETWORK_HPP