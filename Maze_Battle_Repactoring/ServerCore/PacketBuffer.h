#pragma once

class PacketBuffer
{
public:
	PacketBuffer(int32 size);
	
	BYTE* Data() { return _buffer.data(); }
	uint32 Size() { return _size; }
	void  End(uint32 size) { _size = size; }
private:
	vector<BYTE> _buffer;
	uint32 _size;
};
