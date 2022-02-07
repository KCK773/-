#include "ServerPCH.h"
void OutputMemoryStream::ReallocBuffer(uint32_t inNewLength)
{
	tmp = static_cast<char*>(std::realloc(mBuffer, inNewLength));
	//realloc�Լ��� nullptr�� ��ȯ�ϸ� �����ڵ带 �����Ѿ��ϴµ� ���߿� ����
	if (tmp != nullptr)
		mBuffer = tmp;
	mCapacity = inNewLength;
}

void OutputMemoryStream::Write(const void* inData, size_t inByteCount)
{
	//������ ����� Ȯ��
	//mBuffet�� �뷮�� ���ڸ��� �Ǵ°�� ���۰� �ι� Ȯ��
	uint32_t resultHead = mHead + static_cast<uint32_t>(inByteCount);
	if (resultHead > mCapacity)
		ReallocBuffer(std::max(mCapacity * 2, resultHead));

	//������ ���� �տ� ����
	std::memcpy(mBuffer + mHead, inData, inByteCount);

	//mHead�� �������� ���� ��Ͽ� ���
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