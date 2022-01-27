//자료형 안전성을 보강한 UDPSocket 클래스 p.111
//주소를 바인딩하고 데이터그램을 송수신하는 기능이 구현
//앞서 구현한 SocketAddress클래스 활용

class UDPSocket
{
public:
	~UDPSocket();
	int Bind(const SocketAddress& inToAddress);									//SocketAddress를 인자로 받아준다
	int SendTo(const void* inData, int inLen, const SocketAddress& inTo);		//데이터 , 데이터의 길이 , SocketAddress를 인자로 받아준다
	int ReceiveFrom(void* inBuffer, int inLen, SocketAddress& outFrom);

	int SetNonBlockingMode(bool inShouldBeNonBlocking);							//논블로킹 모드로 작동

private:
	friend class SocketUtil;
	UDPSocket(SOCKET inSocket) : mSocket(inSocket) {}							//생성자가 private , SocketUtil에 있는 함수를 이용하여 객체생성
	SOCKET mSocket;
};

using UDPSocketPtr = shared_ptr<UDPSocket>;


