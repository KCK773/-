#include "ServerPCH.h"

UDPSocketPtr SocketUtil::CreateUDPSocket(int inFamily)
{
	SOCKET s = socket(inFamily, SOCK_DGRAM, IPPROTO_UDP);
	if (s != INVALID_SOCKET)
		return UDPSocketPtr(new UDPSocket(s));

	return nullptr;
}

TCPSocketPtr SocketUtil::CreateTCPSocket(int inFamily)
{
	SOCKET s = socket(inFamily, SOCK_STREAM, IPPROTO_TCP);
	if (s != INVALID_SOCKET)
		return TCPSocketPtr(new TCPSocket(s));

	printf("%d", WSAGetLastError());

	return nullptr;
}

fd_set* SocketUtil::FillSetFromVector(fd_set& outSet, const vector<TCPSocketPtr>* inSockets)
{
	if (inSockets)
	{
		FD_ZERO(&outSet);
		for (const TCPSocketPtr& socket : *inSockets)
		{
			FD_SET(socket->mSocket, &outSet);
		}
		return &outSet;
	}
	else return nullptr;
}

void SocketUtil::FillVectorFromSet(vector< TCPSocketPtr >* outSockets, const vector< TCPSocketPtr >* inSockets, const fd_set& inSet)
{
	if (inSockets && outSockets)
	{
		outSockets->clear();
		for (const TCPSocketPtr& socket : *inSockets)
		{
			if (FD_ISSET(socket->mSocket, &inSet))
				outSockets->push_back(socket);
		}
	}
}

int SocketUtil::Select(const vector< TCPSocketPtr >* inReadSet,
						vector< TCPSocketPtr >* outReadSet,
						const vector< TCPSocketPtr >* inWriteSet,
						vector< TCPSocketPtr >* outWriteSet,
						const vector< TCPSocketPtr >* inExceptSet,
						vector< TCPSocketPtr >* outExceptSet)
{
	//받은 vector로 fd_set을 채움
	fd_set read, write, except;
	fd_set* readPtr = FillSetFromVector(read, inReadSet);
	fd_set* writePtr = FillSetFromVector(write, inWriteSet);
	fd_set* exceptPtr = FillSetFromVector(except, inExceptSet);
	int toRet = select(0, readPtr, writePtr, exceptPtr, nullptr);

	if (toRet > 0)
	{
		FillVectorFromSet(outReadSet, inReadSet, read);
		FillVectorFromSet(outWriteSet, inWriteSet, write);
		FillVectorFromSet(outExceptSet, inExceptSet, except);
	}
	return toRet;
}

SocketUtil::~SocketUtil()
{

}