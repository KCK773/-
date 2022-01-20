

//UDP , TCP ��ü�� ���� �� ���� ���� ����Ѵ�.

enum SocketAddressFamily
{
	INET = AF_INET, INET6 = AF_INET6
};

class SocketUtil
{
private:
	SocketUtil();

public:
	static UDPSocketPtr CreateUDPSocket(SocketAddressFamily inFamily);
	//static TCPSocketPtr CreateTCPSocket(SocketAddressFamily inFamily);
	//static void ReportError(std::string msg);
	//static int GetLastError();
	//static fd_set* FillSetFromVector(fd_set& setOut, const std::vector<TCPSocketPtr>* socketsIn);
	virtual ~SocketUtil();
};

