#include "moc_clientmanager.h"

#include "common.h"

ClientManager::ClientManager() {
	clientIdCounter = 0;
}

u32 ClientManager::AddClient(QTcpSocket* clientSocket) {
	u32 tempClientId = clientIdCounter;
	clientIdCounter++;

	auto it = clients.find(clientSocket);
	if (it != clients.end()) {
		throw "AddClient error: Client already exists";
	}

	clients[clientSocket] = tempClientId;

	emit ClientAdded(tempClientId);

	return tempClientId;
}

u32 ClientManager::GetClient(QTcpSocket* clientSocket) {
	auto it = clients.find(clientSocket);
	if (it != clients.end()) {
		return it->second;
	}
	throw "GetClient error: Client doesn't exist";
}

void ClientManager::RemoveClient(QTcpSocket* clientSocket) {
	auto it = clients.find(clientSocket);
	if (it == clients.end()) {
		return;
	}

	emit ClientRemoved(it->second);

	clients.erase(it);
}