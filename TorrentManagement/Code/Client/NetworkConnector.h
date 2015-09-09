#ifndef NETWORK_CONNECTOR_H
#define NETWORK_CONNECTOR_H

#include <vector>

#include "NoiseNetwork\Core\SocketAddress.h"

class NetworkConnector
{
public:
	NetworkConnector(SocketAddress serverAddr);
	~NetworkConnector();

	std::vector<char> send(std::vector<char> data);

private:
	SocketAddress address;

};

#endif