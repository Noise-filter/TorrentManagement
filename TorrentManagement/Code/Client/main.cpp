#include <iostream>
using namespace std;

#include "NoiseNetwork\Core\WinsockFunctions.h"
#include "NoiseNetwork\Core\StreamConnection.h"

#include "NetworkConnector.h"

int main()
{
	if (InitWinSock())
	{
		return 1;
	}

	cout << "Hello World!" << endl;

	StreamConnection socket;

	string ip = "127.0.0.1";
	unsigned short port = 62001;

	SocketAddress address = SocketAddressFactory::Create(ip, port);
	int result = 0;
	vector<char> buffer(100);

	NetworkConnector connector(address);

	while (1)
	{
		buffer = connector.send(buffer);
		cout << buffer.data() << endl;
	}

	ShutdownWinSock();

	return 0;
}