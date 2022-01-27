//UDP , TCP 객체의 생성 및 오류 보고를 담당한다.

/*
enum SocketAddressFamily
{
	INET = AF_INET, INET6 = AF_INET6
};
*/

class SocketUtil
{
private:
	SocketUtil();
	inline static fd_set* FillSetFromVector(fd_set& outSet, const vector< TCPSocketPtr >* inSockets);
	inline static void		FillVectorFromSet(vector< TCPSocketPtr >* outSockets, const vector< TCPSocketPtr >* inSockets, const fd_set& inSet);


public:
	static UDPSocketPtr CreateUDPSocket(int inFamily);
	static TCPSocketPtr CreateTCPSocket(int inFamily);

	static int			Select(const vector< TCPSocketPtr >* inReadSet,
								vector< TCPSocketPtr >* outReadSet,
								const vector< TCPSocketPtr >* inWriteSet,
								vector< TCPSocketPtr >* outWriteSet,
								const vector< TCPSocketPtr >* inExceptSet,
								vector< TCPSocketPtr >* outExceptSet);

	//static void			ReportError(const char* inOperationDesc);
	//static int			GetLastError();
	virtual ~SocketUtil();
};


