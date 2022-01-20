
//�ڷ��� �������� ������ UDPSocket Ŭ����
//�ּҸ� ���ε��ϰ� �����ͱ׷��� �ۼ����ϴ� ����� ����
//�ռ� ������ SocketAddressŬ���� Ȱ��

class TCPSocket;



class UDPSocket
{
public:
	~UDPSocket();	
	int Bind(const SocketAddress& inToAddress);									//SocketAddress�� �޾��ش�
	int SendTo(const void* inData, int inLen , const SocketAddress& inTo);		//������ , �������� ���� , SocketAddress�� �޾��ش�
	int ReceiveFrom(void* inBuffer, int inLen , SocketAddress& outFrom);		
		
private:
	friend class SocketUtil;
	UDPSocket(SOCKET inSocket) : mSocket(inSocket) {}
	SOCKET mSocket;
};

using UDPSocketPtr = shared_ptr<UDPSocket>;