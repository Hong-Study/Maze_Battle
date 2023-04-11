#include "pch.h"
#include "PacketHandler.h"

Func func[(int)PKT_TYPE::COUNT];

void PacketHandler::Init()
{
	for (int i = 0; i < (int)PKT_TYPE::COUNT; i++)
	{
		func[i] = [](BYTE* buffer, uint32 len, SessionRef ref) { return false; };
	}
}

bool PacketHandler::Dispatch(BYTE* buffer, uint32 len, SessionRef ref)
{
	PacketHeader* head = reinterpret_cast<PacketHeader*>(buffer);

	return func[(int)head->type](buffer, len, ref);
}
