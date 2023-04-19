#pragma once

#define BUFSIZE 512
#define PORT 9000

#define ROOM	GET_SINGLE(Room)
#define HANDLER GET_SINGLE(ServerPacketHandler)
#define WINDOW	GET_SINGLE(WindowsCreater)
#define SERVICE	WINDOW->GetService()