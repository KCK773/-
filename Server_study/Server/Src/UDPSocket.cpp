#include "ServerPCH.h"
int UDPSocket::Bind(const SocketAddress& inBindAddress)
{
	int err = bind(mSocket, &inBindAddress.mSockAddr, inBindAddress.GetSize());		//소켓이 어떤 주소와 포트를 직접 바인딩하려면 bind()함수를 호출해야한다.
																					//운영체제에 어떤 소켓이 특정 주소와 전송 계층 포트를 쓰겠다고 알려주는 절차를 바인딩 이라 한다.
	if (err == 0)			//bind함수는 성공시 0 , 실패시 -1을 리턴한다.			//소켓 , 바인딩할 주소 , 주소로 넘긴 sockaddr의 길이를 인자로 받는다
		return NO_ERROR;

	return -1;
	//SocketUtil::ReportError(L"UDPSocket::Bind");
	//return SocketUtil::GetLastError();
}

int UDPSocket::SendTo(const void* inData, int inLen, const SocketAddress& inTo)		//데이터 , 데이터의 길이 , SocketAddress를 받아준다
{
	int byteSentCount = sendto(mSocket, static_cast<const char*>(inData), inLen, 0, &inTo.mSockAddr, inTo.GetSize()); //데이터를 보낼때 seinto() 함수 사용
	//데이터 그램을 보낼 소켓 , 보낼 데이터의 시작주소를 가리키는 포인터 , 데이터의 길이 , 데이터 전송을 제어하는 비트플래그(대부분 게임에서 0) , sockaddr과 sockaddr의 길이

	if (byteSentCount >= 0)	//sendto함수는 성공시 송신 대기열에 넣은 데이터의 길이를 , 이 외에는 -1을 리턴한다.
		return byteSentCount;

	return -1;
	//에러코드를 음수로 리턴
	//SocketUtil::ReportError(L"UDPSocket::SendTo");
	//return -SocketUtil::GetLastError();
}

int UDPSocket::ReceiveFrom(void* inBuffer, int inMaxLength, SocketAddress& outFrom)	//수신한 데이터 그램을 복새하 넣을 버퍼 , buf인자가 담을수 있는 최대 바이트 길이 , SocketAddress를 받아준다
{
	int fromLength = outFrom.GetSize();

	int readByteCount = recvfrom(mSocket, static_cast<char*>(inBuffer), inMaxLength, 0, &outFrom.mSockAddr, &fromLength); //데이터를 받을때 recvfrom()함수 사용
	//데이터를 받으려는 소켓 , 수신한 데이터 그램을 복새하 넣을 버퍼 , buf인자가 담을수 있는 최대 바이트 길이 , 비트플래그 , 발신자의 주소와 포트를 채워줄 곳 , 인자의 길이

	if (readByteCount >= 0) // recvfrom함수는 성공시 buf 에 복사한 데이터의 길이를, 이 외에는 - 1을 리턴한다.
		return readByteCount;

	return -1;
	//에러코드를 음수로 리턴
	//SocketUtil::ReportError(L"UDPSocket::ReceiveFrom");
	//return -SocketUtil::GetLastError();
}

int UDPSocket::SetNonBlockingMode(bool inShouldBeNonBlocking)
{
	u_long arg = inShouldBeNonBlocking ? 1 : 0;				//0이 아닌값이면 논블로킹 , 0이면 블로킹

	int result = ioctlsocket(mSocket, FIONBIO, &arg);

	if (result != SOCKET_ERROR)
		return NO_ERROR;

	return -1;
}

UDPSocket::~UDPSocket()
{
	closesocket(mSocket);	//내부 소켓을 자동으로 닫아주어 소켓이 누수되지 않도록 한다.
}
