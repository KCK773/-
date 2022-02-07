#include "ServerPCH.h"
int TCPSocket::Bind(const SocketAddress& inBindAddress)
{
	int err = bind(mSocket, &inBindAddress.mSockAddr, inBindAddress.GetSize());		//������ � �ּҿ� ��Ʈ�� ���� ���ε��Ϸ��� bind()�Լ��� ȣ���ؾ��Ѵ�.
																					//�ü���� � ������ Ư�� �ּҿ� ���� ���� ��Ʈ�� ���ڴٰ� �˷��ִ� ������ ���ε� �̶� �Ѵ�.
	if (err == 0)			//bind�Լ��� ������ 0 , ���н� -1�� �����Ѵ�.			//���� , ���ε��� �ּ� , �ּҷ� �ѱ� sockaddr�� ���̸� ���ڷ� �޴´�
		return NO_ERROR;

	SocketUtil::ReportError("TCPSocket::Bind");
	return SocketUtil::GetLastError();
}

int TCPSocket::Connect(const SocketAddress& inAddress)
{
	int err = connect(mSocket, &inAddress.mSockAddr, inAddress.GetSize());			// Ŭ���̾�Ʈ�� ���� �̿� , ȣ��� �ش� ���� ������ ������ �ڵ����ŷ ���� ����
	if (err >= 0)			//connect�Լ��� ������ 0 , ���н� -1�� �����Ѵ�.		// ����ϰ��� �ϴ� ���� , ���� ȣ��Ʈ�� �ּҸ� ����Ű�� ������, �������� ���̸� ���ڷ� �޴´�.
		return NO_ERROR;

	SocketUtil::ReportError("TCPSocket::Connect");
	return -SocketUtil::GetLastError();
}

int TCPSocket::Listen(int inBackLog)
{
	int err = listen(mSocket, inBackLog);											// ���� ������ �ڵ����ũ�� �����ϱ� ���� ù�ܰ� �Լ�
	if (err >= 0)			//listen�Լ��� ������ 0 , ���н� -1�� �����Ѵ�.			// ������ ��忡 �� ���ϰ� ������ ������ ��⿭�� �� �ִ� ���ڸ� ����
		return NO_ERROR;

	SocketUtil::ReportError("TCPSocket::Listen");
	return -SocketUtil::GetLastError();
}

TCPSocketPtr TCPSocket::Accept(SocketAddress& inFromAddress)
{
	socklen_t length = inFromAddress.GetSize();
	SOCKET newSocket = accept(mSocket, &inFromAddress.mSockAddr, &length);			//mSocket�� �����׸���� �������� ���⼭ ������ ��û�� �ްԵȴ�.
																					//accept()�� �����ϸ� ���������� �� ������ ������� ���ϵǸ�
	if (newSocket != INVALID_SOCKET)												//�� ������ ���� �� ���� ȣ��Ʈ�� ����ϴ� �뵵�� ���δ�.
		return TCPSocketPtr(new TCPSocket(newSocket));

	SocketUtil::ReportError("TCPSocket::Accept");
	return nullptr;
}

int TCPSocket::Send(const void* inData, int inLen)									//UDP�� �ٸ����� ���� �ø��� �ּ� ������ �Ѱ����� �ʾƵ� �ȴ�.
{																					//TCP������ ���� ȣ��Ʈ�� �ּ� ������ �����ϰ� �ֱ� ����, UDP�ʹ� �޸� �ѹ��� �����Ͱ� ���۵ȴٴ� ������ ����.
	int byteSentCount = send(mSocket, static_cast<const char*>(inData), inLen, 0);

	if (byteSentCount >= 0)
		return byteSentCount;

	SocketUtil::ReportError("TCPSocket::Send");
	return -SocketUtil::GetLastError();
}

int TCPSocket::Receive(void* inData, int inLen)
{
	int bytesReceivedCount = recv(mSocket, static_cast<char*>(inData), inLen, 0);

	if (bytesReceivedCount >= 0)
		return bytesReceivedCount;

	SocketUtil::ReportError("TCPSocket::Receive");
	return -SocketUtil::GetLastError();
}

TCPSocket::~TCPSocket()
{
	closesocket(mSocket);	//���� ������ �ڵ����� �ݾ��־� ������ �������� �ʵ��� �Ѵ�.
}

