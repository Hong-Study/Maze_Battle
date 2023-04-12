#include "pch.h"
#include "ClientPacketHandler.h"

Func func[(int)PKT_TYPE::COUNT];

void ClientPacketHandler::Init()
{
	for (int i = 0; i < (int)PKT_TYPE::COUNT; i++)
	{
		func[i] = [](BYTE* buffer, uint32 len, SessionRef ref) { return false; };
	}
	func[PKT_TYPE::ROOM_CREATE] = [](BYTE* buffer, uint32 len, SessionRef ref) { return HandlerRoomCreate(buffer, len, ref); };
}

bool ClientPacketHandler::Dispatch(BYTE* buffer, uint32 len, SessionRef ref)
{
	PacketHeader* head = reinterpret_cast<PacketHeader*>(buffer);
	int32 pk = sizeof(PacketHeader);
	if (!func[head->type](buffer + pk, len - pk, ref)) {
		cout << "비정상 실행 : " << head->type << endl;
		return false;
	}

	return true;
}

bool ClientPacketHandler::HandlerRoomCreate(BYTE* buffer, uint32 len, SessionRef ref)
{
	return false;
}
