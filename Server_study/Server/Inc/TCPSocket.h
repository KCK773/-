//자료형 안전성을 보강한 TCP 소켓 p.117

class TCPSocket
{
public:
	~TCPSocket();
	int						Bind(const SocketAddress& inToAddress);
	int						Connect(const SocketAddress& inAddress);
	int						Listen(int inBackLog = 32);
	shared_ptr< TCPSocket >	Accept(SocketAddress& inFromAddress);
	int						Send(const void* inData, int inLen);
	int						Receive(void* inBuffer, int inLen);
	
private:
	friend class SocketUtil;
	TCPSocket(SOCKET inSocket) : mSocket(inSocket) { }
	SOCKET mSocket;
};

typedef shared_ptr< TCPSocket > TCPSocketPtr;


