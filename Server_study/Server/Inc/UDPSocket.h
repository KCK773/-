//�ڷ��� �������� ������ UDPSocket Ŭ���� p.111
//�ּҸ� ���ε��ϰ� �����ͱ׷��� �ۼ����ϴ� ����� ����
//�ռ� ������ SocketAddressŬ���� Ȱ��

class UDPSocket
{
public:
	~UDPSocket();
	int Bind(const SocketAddress& inToAddress);									//SocketAddress�� ���ڷ� �޾��ش�
	int SendTo(const void* inData, int inLen, const SocketAddress& inTo);		//������ , �������� ���� , SocketAddress�� ���ڷ� �޾��ش�
	int ReceiveFrom(void* inBuffer, int inLen, SocketAddress& outFrom);

	int SetNonBlockingMode(bool inShouldBeNonBlocking);							//����ŷ ���� �۵�

private:
	friend class SocketUtil;
	UDPSocket(SOCKET inSocket) : mSocket(inSocket) {}							//�����ڰ� private , SocketUtil�� �ִ� �Լ��� �̿��Ͽ� ��ü����
	SOCKET mSocket;
};

using UDPSocketPtr = shared_ptr<UDPSocket>;


