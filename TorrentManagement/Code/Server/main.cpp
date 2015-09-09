#include <iostream>
using namespace std;

#include "NoiseNetwork\Core\WinsockFunctions.h"
#include "NoiseNetwork\Core\ThreadedAcceptServer.h"
#include "NoiseNetwork\Core\StreamConnection.h"

int main()
{
	if (InitWinSock())
	{
		return 1;
	}

	cout << "Hello World!" << endl;

	unsigned short port = 62001;

	ThreadedAcceptServer acceptServer;
	if (!acceptServer.Init(SocketAddressFactory::Create("0.0.0.0", port)))
	{
		int error = GetLastError();
		cout << "Error initializing " + error << endl;
		return 1;
	}

	acceptServer.Start();

	vector<char> buffer;
	string message = "Hello world!";
	buffer.assign(message.begin(), message.end());

	for (;;)
	{
		if (acceptServer.WaitingClients())
		{
			SOCKET socket = acceptServer.GetConnectedClient();
			cout << socket << " connected" << endl;
			StreamSocket client(socket);
			if (client.Send(buffer, buffer.size()) == INVALID_SOCKET)
			{
				int error = WSAGetLastError();
				cout << error << " Error" << endl;
			}
			client.Close();
		}
		else
		{
			Sleep(100);
		}
	}

	acceptServer.Stop();

	ShutdownWinSock();

	return 0;
}