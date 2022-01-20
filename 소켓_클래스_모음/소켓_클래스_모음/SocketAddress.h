

//�ڷ��� �������� Ȯ���� SockAddressŬ����	p.103
//���� �⺻ �ڷ����� �Լ��� ��ü ���� ���·� ���εε��� ���ø����̼� ���ؿ��� ������ �θ� �����ϴ�.

class SocketAddress
{
public:
	SocketAddress(uint32_t inAddress, uint16_t inPort);				//4����Ʈ IP�ּҿ� ��Ʈ ��ȣ�� �޾� �̸� ���� sockaddr ����ü�� ������ ä���
	SocketAddress(const sockaddr& inSockAddr);						//��° �����ڴ� ����Ƽ�� sockaddr ����ü�� �޾� ���� mSockAddr�ʵ忡 �����Ѵ�.
	size_t GetSize() const { return sizeof(sockaddr); }				//�ܼ��ϰ� sockkaddr ���̸� �Ѱܾ� �ϴ� �Լ��� ���ϰ� ����ϱ� ���Ѱ�
			
private:
	friend class UDPSocket;											//UDPSocket���� mSockAddr��������� �����ϱ� ���� ������Ŭ������ �����صд�.
	sockaddr mScokAddr;
	sockaddr_in* GetAsScokAddrIn(){ return reinterpret_cast<sockaddr_in*>(&mScokAddr); }
};

using SocketAddressPtr = shared_ptr<SocketAddress>;


/*
	API�� ��õǾ� �ִ� sockaddr �ڷ��� 
	(��Ʈ��ũ ���� ��Ŷ���� �߽��� �ּҿ� ������ �ּҰ� �ʿ��ϸ� �� �ּ������� ���� ���̺귯���� �ְ�ޱ� ���� API�� sockaddr �ڷ����� ����)
	struct sockaddr
	{
		unit16_t	sa_family;		�ּ��� ������ ��Ÿ���� �����
		char		sa_data[14];	�ּ� �йи��� ���� �پ��� ������ �ּҸ� ����
	};

	IPv4 ��Ŷ�� �ּҸ� ������� sockaddr_in���� ���
	struct sockaddr_in
	{
		short		sin_family;		sa_family�� ���� ���
		unit16_t	sin_port;		��Ʈ���� 16��Ʈ�� ��Ÿ��
		struct	in_addr sin_addr;	IPv4�ּҸ� ��Ÿ��
		char		sin_zero[8];	������� ������ �ϰ��� ������ ���� 0���� ä������ / sockaddr_in�� ũ�⸦ sockaddr�� ���߰� ���Ѱ�
	};
*/