#include "ServerPCH.h"
#include <iostream>
using namespace std;

//소켓 사용전에 꼭!!!! 윈속 초기화 라는것을 먼저 한다.

void DoTCPLoop()
{
	TCPSocketPtr listenSocket = SocketUtil::CreateTCPSocket(AF_INET);
	SocketAddress receivingAddress(INADDR_ANY, 48000);
	if (listenSocket->Bind(receivingAddress) != NO_ERROR)
		return;

	vector<TCPSocketPtr> readBlockSockets;
	readBlockSockets.push_back(listenSocket);
	vector<TCPSocketPtr> readableSockets;

	while (1)
	{
		if (!SocketUtil::Select(&readBlockSockets, &readableSockets, nullptr, nullptr, nullptr, nullptr))
			continue;

		//readableSockets에 받은 패킷을 하나씩 순회한다.
		for (const TCPSocketPtr& socket : readableSockets)
		{
			if (socket == listenSocket)
			{
				//받은 소켓중 하나가 최초의 리스닝소켓이면 신규클라이언트가 접속했다는 뜻이다.
				//리스닝 소켓에서 새 연결을 받는다.
				SocketAddress newClientAddress;
				auto newSocket = listenSocket->Accept(newClientAddress);
				readableSockets.push_back(newSocket);
				cout << "누군가 접속했우" << endl;
			}
			else
			{
				//일반 소켓이므로 데이터를 수신한다.
			}
		}
	}
}

int main()
{	//윈속 초기화
	bool start = SocketUtil::StaticInit();
	if (start == true)
	{
		cout << "윈속 초기화 성공" << endl;
	}
	//서버루프
	DoTCPLoop();

	// 윈속 제거
	SocketUtil::CleanUp();
	return 0;
}
