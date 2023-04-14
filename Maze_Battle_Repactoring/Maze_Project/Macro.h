#pragma once

#define BUFSIZE 512
#define PORT 9000
#define SERVERIP "127.0.0.1"

#define NETWORK GET_SINGLE(NetworkManager)
#define MENU	GET_SINGLE(Menu)

#define NETSOCK	NETWORK->GetService()
#define HANDLER GET_SINGLE(ClientPacketHandler)