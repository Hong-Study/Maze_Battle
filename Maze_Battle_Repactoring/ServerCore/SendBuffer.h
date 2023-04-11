#pragma once
extern thread_local SendBufferChunkRef LSendBufferChunk;

class SendBuffer
{
public:
	SendBuffer(SendBufferChunkRef owner, BYTE* buffer, uint32 allocSize);
	~SendBuffer();

	BYTE*	Data() { return _buffer; }
	int32	GetSize() { return _size; }
	void	Close(uint32 writeSize);

private:
	SendBufferChunkRef	_owner;
	BYTE*				_buffer;
	uint32				_size = 0;
	uint32				_allocSize;
};

class SendBufferChunk : public enable_shared_from_this<SendBufferChunk>
{
	enum
	{
		SEND_BUFFER_CHUNK = 0x1000
	};

public:
	SendBufferChunk();
	~SendBufferChunk();

	void			Reset();
	SendBufferRef	Open(uint32 allocSize);
	void			Close(uint32 writeSize);

	bool			IsOpen() { return _open; }
	BYTE*			Buffer() { return &_buffer[_usedSize]; }
	uint32			FreeSize() { return static_cast<uint32>(_buffer.size()) - _usedSize; }

private:
	Array<BYTE, SEND_BUFFER_CHUNK>	_buffer = {};
	bool							_open = false;
	uint32							_usedSize = 0;
};

class SendBufferPool
{
	SINGLETON(SendBufferPool)

public:
	void				Init() { }
	SendBufferRef		Open(uint32 size);

private:
	SendBufferChunkRef	Pop();
	void				Push(SendBufferChunkRef buffer);

	static void			PushGlobal(SendBufferChunk* buffer);

private:
	vector<SendBufferChunkRef> _sendBufferChunks;
};