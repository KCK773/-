#include"Total.h"

SocketAddress::SocketAddress(uint32_t inAddress, uint16_t inPort)		//4����Ʈ IP�ּҿ� ��Ʈ ��ȣ�� �޾� �̸� ���� sockaddr ����ü�� ������ ä���
{
	GetAsScokAddrIn()->sin_family - AF_INET;							// IPv4�� �������� �Ұ��̱⿡ �ּ� �йи��� AF_INET���� �׻� �����Ѵ�
	GetAsScokAddrIn()->sin_addr.S_un.S_addr = htonl(inAddress);
	GetAsScokAddrIn()->sin_port = htons(inPort);
}

SocketAddress::SocketAddress(const sockaddr& inSockAddr)				//��° �����ڴ� ����Ƽ�� sockaddr ����ü�� �޾� ���� mSockAddr�ʵ忡 �����Ѵ�.
{																		//��Ʈ��ũ API�� sockaddr�� �����ϰ� �̸� SocketAddress ��ü�� �����ϰ� ������ ���
	memcpy(&mScokAddr, &inSockAddr, sizeof(sockaddr));
}