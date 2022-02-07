#define STREAM_ENDIANNESS 0
#define PLATFORM_ENDIANNESS 0

//��ü �ϳ��� ������ �� �� ��ü�� ���õ� �����͸� ���� �ϳ��� ��Ƶξ��ٰ�
//�� ���۸� ��°�� �����ϰ� �����ִ� Ŭ����
//

class OutputMemoryStream //������ �۽Ž�
{
public:
	OutputMemoryStream() : mBuffer(nullptr), mHead(0), mCapacity(0) { ReallocBuffer(32); }
	~OutputMemoryStream() { std::free(mBuffer); } //��ü �Ҹ�� �޸� ����

	//��Ʈ���� ������ ���� ��ġ �����͸� ����
	const char* GetBufferPtr() const { return mBuffer; }
	uint32_t GetLength() const { return mHead; }

	void Write(const void* inData, size_t inByteCount);
	void Write(uint32_t inData) { Write(&inData, sizeof(inData)); }
	void Write(int32_t inData) { Write(&inData, sizeof(inData)); }

	//���� �ڷ����� �ƴ� ���� ����ȭ ���� �ʵ��� �ؾ��Ѵ�.
	template<typename T> void Wirte(const T& inData)
	{
		//���� �ڷ������� ���θ� ������ Ÿ�ӿ� �˻�
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

	// std::vector�� ���ڽ��̹Ƿ� ǥ�� Wirte()�Լ��� �Ἥ  std::vector�� �޸� �ּҸ� ��Ʈ���� ������ ������ �����ϴ�.
	//�̷��� �ϸ�  std::vector���� ���� ������ ������ ���δ�� ����ȭ�ع���, ���� ȣ��Ʈ���� �����ϸ� �����Ⱚ�� ����Ű�� �����Ͱ� �Ǿ������.
	//vector�� ��°�� ����ȭ�ϱ⺸�ٴ� , Ŀ���� ����ȭ �Լ��� �ۼ��� vector�� ����� �����͸� ����ϰ� �������Ѵ�.
	//�̷������� Ư��ȭ�� Write�� Read�� �߰��ϸ� ���� �پ��� ������ �����̳�, �Ǵ� �����ͷ� ������ �����͸� ������ �� �ִ�.
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

class InputMemoryStream //������ ���Ž�
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
