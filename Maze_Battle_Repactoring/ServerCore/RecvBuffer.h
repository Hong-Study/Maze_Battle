#pragma once
class RecvBuffer
{
	enum { BUFFER_COUNT = 10 };
public:
	RecvBuffer(int32 size);
	~RecvBuffer() { }

	void			Clean();
	bool			OnRead(const int32 numOfBytes);
	bool			OnWrite(const int32 numOfBytes);

	BYTE*			ReadPos() { return &_buffer[_readPos]; }
	BYTE*			WritePos() { return &_buffer[_writePos]; }
	int32			DataSize() { return _writePos - _readPos; }
	int32			FreeSize() { return _capacity - _writePos; }

private:
	vector<BYTE> _buffer;
	int32 _capacity = 0;
	int32 _bufferSize = 0;
	int32 _readPos = 0;
	int32 _writePos = 0;
};

