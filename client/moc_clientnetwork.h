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
	bool writeData(PacketNote packet);
	bool writeData(PacketModeConfig packet);
	bool writeData(PacketParamConfig packet);
	bool writeData(PacketScale packet);

private:
	QTcpSocket *socket;
};

#endif//MOC_CLIENTNETWORK_HPP