#include"Total.h"

int UDPSocket::Bind(const SocketAddress& inBindAddress)
{
	int err = bind(mSocket, &inBindAddress.mScokAddr, inBindAddress.GetSize());		//������ � �ּҿ� ��Ʈ�� ���� ���ε��Ϸ��� bind()�Լ��� ȣ���ؾ��Ѵ�.
																					//�ü���� � ������ Ư�� �ּҿ� ���� ���� ��Ʈ�� ���ڴٰ� �˷��ִ� ������ ���ε� �̶� �Ѵ�.
	if (err == 0)			//bind�Լ��� ������ 0 , ���н� -1�� �����Ѵ�.			//���� , ���ε��� �ּ� , �ּҷ� �ѱ� sockaddr�� ���̸� ���ڷ� �޴´�
		return NO_ERROR;

	//SocketUtil::ReportError(L"UDPSocket::Bind");
	//return SocketUtil::GetLastError();
}

int UDPSocket::SendTo(const void* inData, int inLen, const SocketAddress& inTo)		//������ , �������� ���� , SocketAddress�� �޾��ش�
{
	int byteSentCount = sendto(mSocket, static_cast<const char*>(inData), inLen, 0, &inTo.mScokAddr, inTo.GetSize()); //�����͸� ������ seinto() �Լ� ���
	//������ �׷��� ���� ���� , ���� �������� �����ּҸ� ����Ű�� ������ , �������� ���� , ������ ������ �����ϴ� ��Ʈ�÷���(��κ� ���ӿ��� 0) , sockaddr�� sockaddr�� ����

	if (byteSentCount >= 0)	//sendto�Լ��� ������ �۽� ��⿭�� ���� �������� ���̸� , �� �ܿ��� -1�� �����Ѵ�.
		return byteSentCount;
	
	//�����ڵ带 ������ ����
	//SocketUtil::ReportError(L"UDPSocket::SendTo");
	//return -SocketUtil::GetLastError();
}

int UDPSocket::ReceiveFrom(void* inBuffer, int inMaxLength, SocketAddress& outFrom)	//������ ������ �׷��� ������ ���� ���� , buf���ڰ� ������ �ִ� �ִ� ����Ʈ ���� , SocketAddress�� �޾��ش�
{
	int fromLength = outFrom.GetSize();

	int readByteCount = recvfrom(mSocket, static_cast<char*>(inBuffer), inMaxLength, 0, &outFrom.mScokAddr, &fromLength);
	//�����͸� �������� ���� , ������ ������ �׷��� ������ ���� ���� , buf���ڰ� ������ �ִ� �ִ� ����Ʈ ���� , ��Ʈ�÷��� , �߽����� �ּҿ� ��Ʈ�� ä���� �� , ������ ����

	if (readByteCount >= 0) // recvfrom�Լ��� ������ buf �� ������ �������� ���̸�, �� �ܿ��� - 1�� �����Ѵ�.
		return readByteCount;
	
	//�����ڵ带 ������ ����
	//SocketUtil::ReportError(L"UDPSocket::ReceiveFrom");
	//return -SocketUtil::GetLastError();
}

UDPSocket::~UDPSocket()
{
	closesocket(mSocket);	//���� ������ �ڵ����� �ݾ��־� ������ �������� �ʵ��� �Ѵ�.
}