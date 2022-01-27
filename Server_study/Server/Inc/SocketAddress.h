//�ڷ��� �������� Ȯ���� SockAddressŬ����	p.103
//���� �⺻ �ڷ����� �Լ��� ��ü ���� ���·� ���εε��� ���ø����̼� ���ؿ��� ������ �θ� �����ϴ�.

class SocketAddress
{
public:
	SocketAddress(uint32_t inAddress, uint16_t inPort);				//4����Ʈ IP�ּҿ� ��Ʈ ��ȣ�� �޾� �̸� ���� sockaddr ����ü�� ������ ä���
	SocketAddress(const sockaddr& inSockAddr);						//��° �����ڴ� ����Ƽ�� sockaddr ����ü�� �޾� ���� mSockAddr�ʵ忡 �����Ѵ�.
	int GetSize() const { return sizeof(sockaddr); }				//�ܼ��ϰ� sockkaddr ���̸� �Ѱܾ� �ϴ� �Լ��� ���ϰ� ����ϱ� ���Ѱ�
	SocketAddress();

private:
	friend class UDPSocket;											//UDPSocket���� mSockAddr��������� �����ϱ� ���� ������Ŭ������ �����صд�.
	friend class TCPSocket;
	sockaddr mSockAddr;
	sockaddr_in* GetAsSockAddrIn() { return reinterpret_cast<sockaddr_in*>(&mSockAddr); }
};

using SocketAddressPtr = shared_ptr<SocketAddress>;
