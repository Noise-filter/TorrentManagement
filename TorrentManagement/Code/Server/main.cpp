#include <iostream>
using namespace std;

#include "NoiseNetwork\Core\WinsockFunctions.h"
#include "NoiseNetwork\Core\ThreadedAcceptServer.h"
#include "NoiseNetwork\Core\StreamConnection.h"

vector<char> testingScanner();

int main()
{
	vector<char> filenames = testingScanner();

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

			int result = 0;
			int messageSize = filenames.size();
			do
			{
				result = client.Send(filenames, messageSize);
				if (result > 0)
				{
					messageSize -= result;
				}
			} while (result > 0 && messageSize > 0);

			if (result == INVALID_SOCKET)
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

#include "MediaScanner.h"
#include "FileScanner.h"

#include <algorithm>

vector<char> testingScanner()
{
	Collection collection("Test", "C:\\shared2", CollectionType::TV);

	FileScanner scanner;
	File* file = scanner.scan("\\\\NAS/Movies", true);
	int size = sizeof(*file);
	vector<File*> files = *file->getFiles();
	sort(files.begin(), files.end(), [](File* lhs, File* rhs)
	{
		return (*lhs < *rhs);
	});

	string filenames;

	for (File* f : files)
	{
		filenames.append(f->getName() + '|');
		//cout << f->getName() << endl;
	}
	
	return vector<char>(filenames.begin(), filenames.end());
}