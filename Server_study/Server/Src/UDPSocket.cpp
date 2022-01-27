#include "ServerPCH.h"
int UDPSocket::Bind(const SocketAddress& inBindAddress)
{
	int err = bind(mSocket, &inBindAddress.mSockAddr, inBindAddress.GetSize());		//������ � �ּҿ� ��Ʈ�� ���� ���ε��Ϸ��� bind()�Լ��� ȣ���ؾ��Ѵ�.
																					//�ü���� � ������ Ư�� �ּҿ� ���� ���� ��Ʈ�� ���ڴٰ� �˷��ִ� ������ ���ε� �̶� �Ѵ�.
	if (err == 0)			//bind�Լ��� ������ 0 , ���н� -1�� �����Ѵ�.			//���� , ���ε��� �ּ� , �ּҷ� �ѱ� sockaddr�� ���̸� ���ڷ� �޴´�
		return NO_ERROR;

	return -1;
	//SocketUtil::ReportError(L"UDPSocket::Bind");
	//return SocketUtil::GetLastError();
}

int UDPSocket::SendTo(const void* inData, int inLen, const SocketAddress& inTo)		//������ , �������� ���� , SocketAddress�� �޾��ش�
{
	int byteSentCount = sendto(mSocket, static_cast<const char*>(inData), inLen, 0, &inTo.mSockAddr, inTo.GetSize()); //�����͸� ������ seinto() �Լ� ���
	//������ �׷��� ���� ���� , ���� �������� �����ּҸ� ����Ű�� ������ , �������� ���� , ������ ������ �����ϴ� ��Ʈ�÷���(��κ� ���ӿ��� 0) , sockaddr�� sockaddr�� ����

	if (byteSentCount >= 0)	//sendto�Լ��� ������ �۽� ��⿭�� ���� �������� ���̸� , �� �ܿ��� -1�� �����Ѵ�.
		return byteSentCount;

	return -1;
	//�����ڵ带 ������ ����
	//SocketUtil::ReportError(L"UDPSocket::SendTo");
	//return -SocketUtil::GetLastError();
}

int UDPSocket::ReceiveFrom(void* inBuffer, int inMaxLength, SocketAddress& outFrom)	//������ ������ �׷��� ������ ���� ���� , buf���ڰ� ������ �ִ� �ִ� ����Ʈ ���� , SocketAddress�� �޾��ش�
{
	int fromLength = outFrom.GetSize();

	int readByteCount = recvfrom(mSocket, static_cast<char*>(inBuffer), inMaxLength, 0, &outFrom.mSockAddr, &fromLength); //�����͸� ������ recvfrom()�Լ� ���
	//�����͸� �������� ���� , ������ ������ �׷��� ������ ���� ���� , buf���ڰ� ������ �ִ� �ִ� ����Ʈ ���� , ��Ʈ�÷��� , �߽����� �ּҿ� ��Ʈ�� ä���� �� , ������ ����

	if (readByteCount >= 0) // recvfrom�Լ��� ������ buf �� ������ �������� ���̸�, �� �ܿ��� - 1�� �����Ѵ�.
		return readByteCount;

	return -1;
	//�����ڵ带 ������ ����
	//SocketUtil::ReportError(L"UDPSocket::ReceiveFrom");
	//return -SocketUtil::GetLastError();
}

int UDPSocket::SetNonBlockingMode(bool inShouldBeNonBlocking)
{
	u_long arg = inShouldBeNonBlocking ? 1 : 0;				//0�� �ƴѰ��̸� ����ŷ , 0�̸� ���ŷ

	int result = ioctlsocket(mSocket, FIONBIO, &arg);

	if (result != SOCKET_ERROR)
		return NO_ERROR;

	return -1;
}

UDPSocket::~UDPSocket()
{
	closesocket(mSocket);	//���� ������ �ڵ����� �ݾ��־� ������ �������� �ʵ��� �Ѵ�.
}
