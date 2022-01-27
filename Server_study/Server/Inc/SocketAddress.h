//자료형 안정성이 확보된 SockAddress클래스	p.103
//소켓 기본 자료형과 함수를 객체 지향 형태로 감싸두도록 애플리케이션 수준에서 구현해 두면 유용하다.

class SocketAddress
{
public:
	SocketAddress(uint32_t inAddress, uint16_t inPort);				//4바이트 IP주소와 포트 번호를 받아 이를 내부 sockaddr 구조체의 값으로 채운다
	SocketAddress(const sockaddr& inSockAddr);						//둘째 생성자는 네이티브 sockaddr 구조체를 받아 내부 mSockAddr필드에 복사한다.
	int GetSize() const { return sizeof(sockaddr); }				//단순하게 sockkaddr 길이를 넘겨야 하는 함수를 편하게 사용하기 위한것
	SocketAddress();

private:
	friend class UDPSocket;											//UDPSocket에서 mSockAddr멤버변수에 접근하기 위해 프렌드클래스로 선언해둔다.
	friend class TCPSocket;
	sockaddr mSockAddr;
	sockaddr_in* GetAsSockAddrIn() { return reinterpret_cast<sockaddr_in*>(&mSockAddr); }
};

using SocketAddressPtr = shared_ptr<SocketAddress>;
