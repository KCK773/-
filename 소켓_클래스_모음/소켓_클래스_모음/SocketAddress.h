

//자료형 안정성이 확보된 SockAddress클래스	p.103
//소켓 기본 자료형과 함수를 객체 지향 형태로 감싸두도록 애플리케이션 수준에서 구현해 두면 유용하다.

class SocketAddress
{
public:
	SocketAddress(uint32_t inAddress, uint16_t inPort);				//4바이트 IP주소와 포트 번호를 받아 이를 내부 sockaddr 구조체의 값으로 채운다
	SocketAddress(const sockaddr& inSockAddr);						//둘째 생성자는 네이티브 sockaddr 구조체를 받아 내부 mSockAddr필드에 복사한다.
	size_t GetSize() const { return sizeof(sockaddr); }				//단순하게 sockkaddr 길이를 넘겨야 하는 함수를 편하게 사용하기 위한것
			
private:
	friend class UDPSocket;											//UDPSocket에서 mSockAddr멤버변수에 접근하기 위해 프렌드클래스로 선언해둔다.
	sockaddr mScokAddr;
	sockaddr_in* GetAsScokAddrIn(){ return reinterpret_cast<sockaddr_in*>(&mScokAddr); }
};

using SocketAddressPtr = shared_ptr<SocketAddress>;


/*
	API에 명시되어 있는 sockaddr 자료형 
	(네트워크 계층 패킷에는 발신지 주소와 목적지 주소가 필요하며 이 주소정보를 소켓 라이브러리와 주고받기 위해 API에 sockaddr 자료형이 정의)
	struct sockaddr
	{
		unit16_t	sa_family;		주소의 종류를 나타내는 상숫값
		char		sa_data[14];	주소 패밀리에 따라 다양핸 포맷의 주소를 담음
	};

	IPv4 패킷용 주소를 만들려면 sockaddr_in형을 사용
	struct sockaddr_in
	{
		short		sin_family;		sa_family와 같은 기능
		unit16_t	sin_port;		포트값을 16비트로 나타냄
		struct	in_addr sin_addr;	IPv4주소를 나타냄
		char		sin_zero[8];	사용하지 않으며 일관성 유지를 위해 0으로 채워넣음 / sockaddr_in의 크기를 sockaddr와 맞추가 위한것
	};
*/