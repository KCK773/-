#include "ServerPCH.h"
int TCPSocket::Bind(const SocketAddress& inBindAddress)
{
	int err = bind(mSocket, &inBindAddress.mSockAddr, inBindAddress.GetSize());		//소켓이 어떤 주소와 포트를 직접 바인딩하려면 bind()함수를 호출해야한다.
																					//운영체제에 어떤 소켓이 특정 주소와 전송 계층 포트를 쓰겠다고 알려주는 절차를 바인딩 이라 한다.
	if (err == 0)			//bind함수는 성공시 0 , 실패시 -1을 리턴한다.			//소켓 , 바인딩할 주소 , 주소로 넘긴 sockaddr의 길이를 인자로 받는다
		return NO_ERROR;

	SocketUtil::ReportError("TCPSocket::Bind");
	return SocketUtil::GetLastError();
}

int TCPSocket::Connect(const SocketAddress& inAddress)
{
	int err = connect(mSocket, &inAddress.mSockAddr, inAddress.GetSize());			// 클라이언트측 에서 이용 , 호출시 해당 원격 서버에 접속해 핸드셰이킹 절차 시작
	if (err >= 0)			//connect함수는 성공시 0 , 실패시 -1을 리턴한다.		// 사용하고자 하는 소켓 , 원격 호스트의 주소를 가리키는 포인터, 포인터의 길이를 인자로 받는다.
		return NO_ERROR;

	SocketUtil::ReportError("TCPSocket::Connect");
	return -SocketUtil::GetLastError();
}

int TCPSocket::Listen(int inBackLog)
{
	int err = listen(mSocket, inBackLog);											// 서버 측에서 핸드셰이크를 시작하기 위한 첫단계 함수
	if (err >= 0)			//listen함수는 성공시 0 , 실패시 -1을 리턴한다.			// 리스닝 모드에 둘 소켓과 들어오는 연결을 대기열에 둘 최대 숫자를 지정
		return NO_ERROR;

	SocketUtil::ReportError("TCPSocket::Listen");
	return -SocketUtil::GetLastError();
}

TCPSocketPtr TCPSocket::Accept(SocketAddress& inFromAddress)
{
	socklen_t length = inFromAddress.GetSize();
	SOCKET newSocket = accept(mSocket, &inFromAddress.mSockAddr, &length);			//mSocket는 리스닝모드의 서켓으로 여기서 들어오는 요청을 받게된다.
																					//accept()가 성공하면 내부적으로 새 소켓이 만들어져 리턴되며
	if (newSocket != INVALID_SOCKET)												//이 소켓은 이후 그 원격 호스트와 통신하는 용도로 쓰인다.
		return TCPSocketPtr(new TCPSocket(newSocket));

	SocketUtil::ReportError("TCPSocket::Accept");
	return nullptr;
}

int TCPSocket::Send(const void* inData, int inLen)									//UDP와 다른점은 전송 시마다 주소 정보를 넘겨주지 않아도 된다.
{																					//TCP소켓이 원격 호스트의 주소 정보를 간직하고 있기 때문, UDP와는 달리 한번에 데이터가 전송된다는 보장은 없다.
	int byteSentCount = send(mSocket, static_cast<const char*>(inData), inLen, 0);

	if (byteSentCount >= 0)
		return byteSentCount;

	SocketUtil::ReportError("TCPSocket::Send");
	return -SocketUtil::GetLastError();
}

int TCPSocket::Receive(void* inData, int inLen)
{
	int bytesReceivedCount = recv(mSocket, static_cast<char*>(inData), inLen, 0);

	if (bytesReceivedCount >= 0)
		return bytesReceivedCount;

	SocketUtil::ReportError("TCPSocket::Receive");
	return -SocketUtil::GetLastError();
}

TCPSocket::~TCPSocket()
{
	closesocket(mSocket);	//내부 소켓을 자동으로 닫아주어 소켓이 누수되지 않도록 한다.
}

