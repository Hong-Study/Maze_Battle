#include "pch.h"
#include "PacketHandler.h"

void PacketHandler::Init()
{
	for (int i = 0; i < PKT_TYPE::COUNT; i++)
	{
		func[i] = [](shared_ptr<PacketHandler> ptr, BYTE* buffer, uint32 len, SessionRef ref) { return false; };
	}
	func[PKT_TYPE::ROOM_CREATE] = [](shared_ptr<PacketHandler> ptr, BYTE* buffer, uint32 len, SessionRef ref) {return ptr->HandlerRoomCreate(buffer, len, ref); };
	func[PKT_TYPE::LOGIN] = [](shared_ptr<PacketHandler> ptr, BYTE* buffer, uint32 len, SessionRef ref) {return ptr->HandlerLogin(buffer, len, ref); };
}

bool PacketHandler::Dispatch(BYTE* buffer, uint32 len, SessionRef ref)
{
	PacketHeader* head = reinterpret_cast<PacketHeader*>(buffer);
	int32 pk = sizeof(PacketHeader);
	cout << head->type << " " << head->size << endl;
	if (!func[head->type](nullptr, buffer + pk, len - pk, ref)) {
		cout << "비정상 실행 : " << head->type << endl;
		return false;
	}
	return true;
}