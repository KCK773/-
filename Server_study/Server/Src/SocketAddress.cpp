#include "ServerPCH.h"

SocketAddress::SocketAddress(uint32_t inAddress, uint16_t inPort)		//4바이트 IP주소와 포트 번호를 받아 이를 내부 sockaddr 구조체의 값으로 채운다
{
	GetAsSockAddrIn()->sin_family = AF_INET;							// IPv4를 기준으로 할것이기에 주소 패밀리는 AF_INET으로 항상 지정한다
	GetAsSockAddrIn()->sin_addr.S_un.S_addr = htonl(inAddress);
	GetAsSockAddrIn()->sin_port = htons(inPort);
}

SocketAddress::SocketAddress(const sockaddr& inSockAddr)				//둘째 생성자는 네이티브 sockaddr 구조체를 받아 내부 mSockAddr필드에 복사한다.
{																		//네트워크 API가 sockaddr을 리턴하고 이를 SocketAddress 객체로 래핑하고 싶을때 사용
	memcpy(&mSockAddr, &inSockAddr, sizeof(sockaddr));
}

SocketAddress::SocketAddress()
{
	GetAsSockAddrIn()->sin_family = AF_INET;
	GetAsSockAddrIn()->sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	GetAsSockAddrIn()->sin_port = 0;
}