//������ ������ IP�ּҷ� ��ȯ�Ҷ� ����ϴ� �Լ� "getaddrinfo()" ����� ĸ��ȭ ��Ų��

class SocketAddressFactory
{
public:
	static SocketAddressPtr CreateIPv4FromString(const string& inString);
};