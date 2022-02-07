#include "ServerPCH.h"

bool SocketUtil::StaticInit() //소켓 라이브러리 활성화
{
#if _WIN32
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != NO_ERROR)
	{
		ReportError("Starting Up");
		return false;
	}
#endif
	return true;
}

void SocketUtil::CleanUp() //소켓 라이브러리 종료
{
#if _WIN32
	WSACleanup();
#endif
}

void SocketUtil::ReportError(const char* inOperationDesc) //오류 리포트
{
#if _WIN32
	LPVOID lpMsgBuf;
	DWORD errorNum = GetLastError();

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		errorNum,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&lpMsgBuf,
		0, NULL);


	LOG("Error %s: %d- %s", inOperationDesc, errorNum, lpMsgBuf);
#else
	LOG("Error: %hs", inOperationDesc);
#endif
}

int SocketUtil::GetLastError() //마지막 오류 출력
{
#if _WIN32
	return WSAGetLastError();
#else
	return errno;
#endif

}

UDPSocketPtr SocketUtil::CreateUDPSocket(int inFamily) //UDP소켓 생성
{
	SOCKET s = socket(inFamily, SOCK_DGRAM, IPPROTO_UDP);
	if (s != INVALID_SOCKET)
		return UDPSocketPtr(new UDPSocket(s));

	ReportError("SocketUtil::CreateUDPSocket");
	return nullptr;
}

TCPSocketPtr SocketUtil::CreateTCPSocket(int inFamily) //TCP소켓 생성
{
	SOCKET s = socket(inFamily, SOCK_STREAM, IPPROTO_TCP);
	if (s != INVALID_SOCKET)
		return TCPSocketPtr(new TCPSocket(s));

	ReportError("SocketUtil::CreateTCPSocket");
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