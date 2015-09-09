#include "NetworkConnector.h"

#include "NoiseNetwork\Core\StreamConnection.h"

using namespace std;

NetworkConnector::NetworkConnector(SocketAddress serverAddr)
{
	this->address = serverAddr;
}

NetworkConnector::~NetworkConnector()
{}

std::vector<char> NetworkConnector::send(std::vector<char> data)
{
	vector<char> buffer(1000);
	StreamConnection connection;
	
	if (!connection.Connect(address))
	{
		return buffer;
	}

	int result = 0;
	result = connection.Send(data, data.size());
	if (result <= 0)
	{
		connection.Disconnect();
		return buffer;
	}

	result = connection.Recv(buffer, 1000);

	connection.Disconnect();

	return buffer;
}