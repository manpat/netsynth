#ifndef MOC_SERVERNETWORK_HPP
#define MOC_SERVERNETWORK_HPP

#include <QtCore/QtCore>
#include <QtNetwork/QtNetwork>

class ServerNetwork : public QObject {
	Q_OBJECT
public:
	explicit ServerNetwork(QObject *parent = 0);

signals:
	void dataReceived(QByteArray);

private slots:
	void newConnection();
	void disconnected();
	void readyRead();

private:
	QTcpServer *server;
	QHash<QTcpSocket*, QByteArray*> buffers;
};

#endif//MOC_SERVERNETWORK_HPP