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

	std::string buffer2;
	vector<char> tempBuffer(1000);
	do
	{
		result = connection.Recv(tempBuffer, 1000);
		if (result > 0)
		{
			buffer2.append(tempBuffer.data());
		}
	} while (result > 0);

	int error = WSAGetLastError();
	//cout << error << " Error" << endl;
	connection.Disconnect();

	return buffer;
}