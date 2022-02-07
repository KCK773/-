#define STREAM_ENDIANNESS 0
#define PLATFORM_ENDIANNESS 0

//객체 하나를 전송할 때 그 객체와 관련된 데이터를 버퍼 하나에 모아두었다가
//그 버퍼를 통째로 전송하게 도와주는 클래스
//

class OutputMemoryStream //데이터 송신시
{
public:
	OutputMemoryStream() : mBuffer(nullptr), mHead(0), mCapacity(0) { ReallocBuffer(32); }
	~OutputMemoryStream() { std::free(mBuffer); } //객체 소멸시 메모리 해제

	//스트림의 데이터 시작 위치 포인터를 구함
	const char* GetBufferPtr() const { return mBuffer; }
	uint32_t GetLength() const { return mHead; }

	void Write(const void* inData, size_t inByteCount);
	void Write(uint32_t inData) { Write(&inData, sizeof(inData)); }
	void Write(int32_t inData) { Write(&inData, sizeof(inData)); }

	//원시 자료형이 아닌 것은 직렬화 하지 않도록 해야한다.
	template<typename T> void Wirte(const T& inData)
	{
		//원시 자료형인지 여부를 컴파일 타임에 검사
		static_assert(std::is_arithmetic<T>::value || std::is_enum<T>::value,
			"Generic Write only supports primitive data types");

		if (STREAM_ENDIANNESS == PLATFORM_ENDIANNESS)
		{
			Write(&inData, sizeof(inData));
		}
		else
		{
			T swappedData = ByteSwap(inData);
			Write(&swappedData, sizeof(swappedData));
		}
	}

	// std::vector는 블랙박스이므로 표준 Wirte()함수를 써서  std::vector의 메모리 주소를 스트림에 복사해 넣으면 위험하다.
	//이렇게 하면  std::vector안의 여러 포인터 값들을 무턱대고 직렬화해버려, 원격 호스트에서 복원하면 쓰레기값을 가리키는 포인터가 되어버린다.
	//vector을 통째로 직렬화하기보다는 , 커스텀 직렬화 함수를 작성해 vector에 저장된 데이터만 기록하게 만들어야한다.
	//이런식으로 특수화된 Write와 Read를 추가하면 더욱 다양한 형태의 컨테이너, 또는 포인터로 참조된 데이터를 지원할 수 있다.
	void Write(const std::vector< int >& inIntVector);

	template< typename T >
	void Write(const std::vector< T >& inVector)
	{
		uint32_t elementCount = inVector.size();
		Write(elementCount);
		for (const T& element : inVector)
		{
			Write(element);
		}
	}

private:
	void ReallocBuffer(uint32_t inNewLength);

	char* mBuffer;
	char* tmp;
	uint32_t mHead;
	uint32_t mCapacity;
};

class InputMemoryStream //데이터 수신시
{
public:
	InputMemoryStream(char* inBuffer, uint32_t inByteCount) : mBuffer(inBuffer), mCapacity(inByteCount), mHead(0) {}

	~InputMemoryStream() { std::free( mBuffer ); }

	uint32_t GetRemainingDataSize() const { return mCapacity - mHead; }

	void Read(void* outData, uint32_t inByteCount);
	void Read(uint32_t& outData) { Read(&outData, sizeof(outData)); }
	void Read(int32_t& outData) { Read(&outData, sizeof(outData)); }

	template< typename T > void Read(T& outData)
	{
		static_assert(std::is_arithmetic< T >::value ||
			std::is_enum< T >::value,
			"Generic Read only supports primitive data types");
		Read(&outData, sizeof(outData));
	}

	template< typename T > void Read(std::vector< T >& outVector)
	{
		size_t elementCount;
		Read(elementCount);
		outVector.resize(elementCount);
		for (const T& element : outVector)
		{
			Read(element);
		}
	}

private:
	char* mBuffer;
	uint32_t mHead;
	uint32_t mCapacity;
};

const uint32_t kMaxpacketSize = 1470;
