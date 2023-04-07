#include "pch.h"
#include "PacketBuffer.h"

PacketBuffer::PacketBuffer(int32 size)
	:_size(size)
{
	_buffer.reserve(size);
}
