#pragma once

using Func = std::function<bool(BYTE*, uint32, SessionRef)>;
extern Func func[(int)PKT_TYPE::COUNT];

class PacketHandler
{
public:
	static void Init();
	static bool Dispatch(BYTE* buffer, uint32 len, SessionRef ref);

public:
};
