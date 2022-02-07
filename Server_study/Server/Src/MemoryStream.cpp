#include "ServerPCH.h"
void OutputMemoryStream::ReallocBuffer(uint32_t inNewLength)
{
	tmp = static_cast<char*>(std::realloc(mBuffer, inNewLength));
	//realloc함수가 nullptr을 반환하면 에러코드를 일으켜야하는데 나중에 하자
	if (tmp != nullptr)
		mBuffer = tmp;
	mCapacity = inNewLength;
}

void OutputMemoryStream::Write(const void* inData, size_t inByteCount)
{
	//공간을 충분히 확보
	//mBuffet의 용량이 모자르게 되는경우 버퍼가 두배 확장
	uint32_t resultHead = mHead + static_cast<uint32_t>(inByteCount);
	if (resultHead > mCapacity)
		ReallocBuffer(std::max(mCapacity * 2, resultHead));

	//버퍼의 제일 앞에 복사
	std::memcpy(mBuffer + mHead, inData, inByteCount);

	//mHead를 전진시켜 다음 기록에 대비
	mHead = resultHead;
}

void OutputMemoryStream:: Write(const std::vector< int >& inIntVector)
{
	size_t elementCount = inIntVector.size();
	Write(elementCount);
	Write(inIntVector.data(), elementCount * sizeof(int));
}

void InputMemoryStream::Read(void* outData, uint32_t inByteCount)
{
	uint32_t resultHead = mHead + inByteCount;
	if (resultHead > mCapacity)
	{
		//handle error, no data to read!
		//...
	}

	std::memcpy(outData, mBuffer + mHead, inByteCount);

	mHead = resultHead;
}