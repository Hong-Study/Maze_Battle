#include "pch.h"
#include "SendBuffer.h"
#include "ObjectPool.h"

thread_local SendBufferChunkRef LSendBufferChunk;


SendBuffer::SendBuffer(SendBufferChunkRef owner, BYTE* buffer, uint32 allocSize)
	: _owner(owner), _buffer(buffer), _allocSize(allocSize)
{
}

SendBuffer::~SendBuffer()
{
}

void SendBuffer::Close(uint32 size)
{
	ASSERT_CRASH(_allocSize >= size);
	_size = size;
	_owner->Close(size);
}

SendBufferRef SendBufferPool::Open(uint32 size)
{
	if (LSendBufferChunk == nullptr) {
		LSendBufferChunk = Pop();
		LSendBufferChunk->Reset();
	}

	if (LSendBufferChunk->FreeSize() < size) {
		LSendBufferChunk = Pop();
		LSendBufferChunk->Reset();
	}

	return LSendBufferChunk->Open(size);
}

SendBufferChunkRef SendBufferPool::Pop()
{
	if (_sendBufferChunks.empty() == false)
	{
		SendBufferChunkRef sendBufferChunk = _sendBufferChunks.back();
		_sendBufferChunks.pop_back();
		return sendBufferChunk;
	}
	
	return SendBufferChunkRef(xnew<SendBufferChunk>(), PushGlobal);
}

void SendBufferPool::Push(SendBufferChunkRef buffer)
{
	_sendBufferChunks.push_back(buffer);
}

void SendBufferPool::PushGlobal(SendBufferChunk* buffer)
{
	SENDBUF->Push(SendBufferChunkRef(buffer, PushGlobal));
}

SendBufferChunk::SendBufferChunk()
{
}

SendBufferChunk::~SendBufferChunk()
{
}

void SendBufferChunk::Reset()
{
	_open = false; 
	_usedSize = 0;
}

SendBufferRef SendBufferChunk::Open(uint32 allocSize)
{
	ASSERT_CRASH(allocSize <= SEND_BUFFER_CHUNK);
	ASSERT_CRASH(_open == false);

	if (allocSize > FreeSize())
		return nullptr;

	_open = true;
		
	return ObjectPool<SendBuffer>::MakeShared(shared_from_this(), Buffer(), allocSize);
}

void SendBufferChunk::Close(uint32 writeSize)
{
	ASSERT_CRASH(_open == true);
	_open = false;
	_usedSize += writeSize;
}
