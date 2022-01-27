//도메인 네임을 IP주소로 변환할때 사용하는 함수 "getaddrinfo()" 기능을 캡슐화 시킨것

class SocketAddressFactory
{
public:
	static SocketAddressPtr CreateIPv4FromString(const string& inString);
};