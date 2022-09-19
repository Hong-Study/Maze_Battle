#include "pch.h"
#include <iostream>
#include "CorePch.h"
#include "NetWorking.h"
#include "Room.h"
#include "CreateMap.h"

int main()
{
    //윈속 초기화
    NetWorking::Init();
    Room::Init();

    //소켓 생성
    SOCKET listen_s = NetWorking::CreateSocket();
    if (listen_s == INVALID_SOCKET)
        NetWorking::err_quit("socket");

    if(!NetWorking::BindAnyAddress(listen_s, PORT)) NetWorking::err_quit("Bind");
    if(!NetWorking::Listen(listen_s, SOMAXCONN)) NetWorking::err_quit("listen");
    
    NetWorking::AddScoketInfo(listen_s, 0);


    //데이터 통신에 사용할 변수
    WSANETWORKEVENTS NetworkEvents;
    SOCKET clientsock;
    SOCKADDR_IN clientaddr;
    int addrlen, i, retVal;
    while (1) {
        //이벤트 객체 관찰
        i = NetWorking::WaitForMultipleEvent();
        if (i == WSA_WAIT_FAILED) continue;

        i -= WSA_WAIT_EVENT_0;

        retVal = NetWorking::NetWorkEvent(i, NetworkEvents);
        if (retVal == SOCKET_ERROR) continue;

        //FD_ACCEPT 이벤트 처리
        if (NetworkEvents.lNetworkEvents & FD_ACCEPT) {
            if (NetworkEvents.iErrorCode[FD_ACCEPT_BIT] != 0) {
                NetWorking::err_quit("NetworkEvents.iErrorCode[FD_ACCEPT_BIT]");
                continue;
            }
            addrlen = sizeof(clientaddr);
            clientsock = accept(NetWorking::GetSocketInfo(i)->GetSocket(), (SOCKADDR*)&clientaddr, &addrlen);
            if (clientsock == INVALID_SOCKET) {
                NetWorking::err_quit("Accept()");
                continue;
            }
            cout << "[TCP서버] 클라이언트 접속 IP : " << inet_ntoa(clientaddr.sin_addr) << " " << ntohs(clientaddr.sin_port) << endl;
            if (NetWorking::GetTotalSockets() >= WSA_MAXIMUM_WAIT_EVENTS) {
                cout << "[오류] 더이상 접속을 받아들일 수 없습니다." << endl;
                closesocket(clientsock);
                continue;
            }
            if(!NetWorking::AddScoketInfo(clientsock, -1))
                continue;
        }

        //FD_READ 이벤트 처리
        if (NetworkEvents.lNetworkEvents & FD_READ) {
            if ((NetworkEvents.lNetworkEvents & FD_READ) && (NetworkEvents.iErrorCode[FD_READ_BIT] != 0)) {
                NetWorking::err_display(NetworkEvents.iErrorCode[FD_READ_BIT]);
                continue;
            }
            Datas* socket = NetWorking::GetSocketInfo(i);
            retVal = recv(socket->GetSocket(), reinterpret_cast<char*>(socket->GetLoby_Data()), 512, 0);
            if (retVal == SOCKET_ERROR) {
                if (WSAGetLastError() != WSAEWOULDBLOCK) {
                    NetWorking::err_quit("recv()");
                }
                continue;
            }
            cout << "Recv : " << retVal << endl;

            //게임 시작
            if (socket->GetLoby_Data()->GameStart) {
                int N = socket->GetLoby_Data()->RoomNumber;
                bool win = true;
                if (socket->GetLoby_Data()->Win) {
                    if (socket->GetLoby_Data()->Type == 1) {
                        Datas* client = NetWorking::GetSocketInfo(Room::GetClientIndex(socket->GetLoby_Data()->RoomNumber));
                        send(client->GetSocket(), reinterpret_cast<char*>(&win), sizeof(bool), 0);
                        send(socket->GetSocket(), reinterpret_cast<char*>(&win), sizeof(bool), 0);
                    }
                    else {
                        Datas* host = NetWorking::GetSocketInfo(Room::GetHostIndex(socket->GetLoby_Data()->RoomNumber));
                        send(host->GetSocket(), reinterpret_cast<char*>(&win), sizeof(bool), 0);
                        send(socket->GetSocket(), reinterpret_cast<char*>(&win), sizeof(bool), 0);
                    }
                }
                else {
                    Room::GameMaps[N] = new CreateMap(socket->GetLoby_Data()->Level);
                    socket->GetLoby_Data()->Type = 3;
                    if (Room::GetClientIndex(socket->GetLoby_Data()->RoomNumber) != -1) {
                        Datas* client = NetWorking::GetSocketInfo(Room::GetClientIndex(socket->GetLoby_Data()->RoomNumber));
                        client->GetLoby_Data()->Type = 3;
                        client->GetLoby_Data()->GameStart = true;

                        send(socket->GetSocket(), reinterpret_cast<char*>(socket->GetLoby_Data()), sizeof(*(socket->GetLoby_Data())), 0);
                        send(client->GetSocket(), reinterpret_cast<char*>(client->GetLoby_Data()), sizeof(*(client->GetLoby_Data())), 0);

                        int _size = socket->GetLoby_Data()->Level * 10 + 1;
                        int len = sizeof(Room::GameMaps[N]->_board[0][0]);

                        retVal = send(socket->GetSocket(), reinterpret_cast<char*>(&len), sizeof(int), 0);
                        retVal = send(client->GetSocket(), reinterpret_cast<char*>(&len), sizeof(int), 0);

                        for (int i = 0; i < _size; i++) {
                            for (int j = 0; j < _size; j++) {
                                send(socket->GetSocket(), reinterpret_cast<char*>(&(Room::GameMaps[N]->_board[i][j])), len, 0);
                                send(client->GetSocket(), reinterpret_cast<char*>(&(Room::GameMaps[N]->_board[i][j])), len, 0);
                            }
                        }
                        client->GetLoby_Data()->Type = 2;
                        socket->GetLoby_Data()->Type = 1;
                    }
                    else {
                        socket->GetLoby_Data()->GameStart = false;
                        send(socket->GetSocket(), reinterpret_cast<char*>(socket->GetLoby_Data()), sizeof(*(socket->GetLoby_Data())), 0);
                    }
                }
            }
            //이외 상황
            else {
                if (socket->GetLoby_Data()->Type == 1 ) {
                    socket->GetLoby_Data()->RoomNumber = Room::GetHostSize();
                    send(socket->GetSocket(), reinterpret_cast<char*>(&(socket->GetLoby_Data()->RoomNumber)), sizeof(int), 0);
                    Room::PushHost(i);
                }

                //Clinet 로비 입장 시 패킷 처리
                else if (socket->GetLoby_Data()->Type == 2) {
                    //Loby 입장 시처리 
                    if (socket->GetLoby_Data()->RoomNumber == -1) {
                        //호스트 갯수
                        int size = Room::GetHostSize();
                        socket->GetLoby_Data()->RoomNumber = size;

                        //보낼 길이 측정
                        int len = 0;
                        Datas* data;
                        for (int j = 0; j < size; j++) {
                            data = NetWorking::GetSocketInfo(Room::GetHostIndex(j));
                            len = sizeof(*(data->GetLoby_Data()));

                            retVal = send(socket->GetSocket(), reinterpret_cast<const char*>(&len), sizeof(int), 0);
                            retVal = send(socket->GetSocket(), reinterpret_cast<const char*>(data->GetLoby_Data()), len, 0);
                            cout << "데이터 전송 : " << retVal << endl;
                        }
                        len = 0;
                        send(socket->GetSocket(), reinterpret_cast<char*>(&len), sizeof(int), 0);
                    }
                    //Room 입장시 Host와 Client에 서로의 정보 전달
                    else {
                        if (Room::CheckIndex(socket->GetLoby_Data()->RoomNumber)) {
                            Datas* data;

                            data = NetWorking::GetSocketInfo(Room::GetHostIndex(socket->GetLoby_Data()->RoomNumber));

                            socket->GetLoby_Data()->Level = data->GetLoby_Data()->Level;
                            send(socket->GetSocket(), reinterpret_cast<char*>(socket->GetLoby_Data()), sizeof(*(socket->GetLoby_Data())), 0);

                            Room::PushClient(socket->GetLoby_Data()->RoomNumber, i);
                            send(data->GetSocket(), reinterpret_cast<char*>(socket->GetLoby_Data()), sizeof(*(socket->GetLoby_Data())), 0);
                            send(socket->GetSocket(), reinterpret_cast<char*>(data->GetLoby_Data()), sizeof(*(data->GetLoby_Data())), 0);

                        }
                        else {
                            socket->GetLoby_Data()->RoomNumber = -1;
                            send(socket->GetSocket(), reinterpret_cast<char*>(socket->GetLoby_Data()), sizeof(*(socket->GetLoby_Data())), 0);
                        }
                    }
                }
                //Client 측에서 방 나올때 전달
                else if (socket->GetLoby_Data()->Type == -1) {
                    Datas* data = data = NetWorking::GetSocketInfo(Room::GetHostIndex(socket->GetLoby_Data()->RoomNumber));
                    send(socket->GetSocket(), reinterpret_cast<char*>(socket->GetLoby_Data()), sizeof(*(socket->GetLoby_Data())), 0);
                    send(data->GetSocket(), reinterpret_cast<char*>(socket->GetLoby_Data()), sizeof(*(socket->GetLoby_Data())), 0);
                    
                    Room::DeleteClient(NetWorking::GetSocketInfo(i)->GetLoby_Data()->RoomNumber);
                }
            }
        }

       /* if (NetworkEvents.lNetworkEvents & FD_WRITE) {
            if ((NetworkEvents.lNetworkEvents & FD_WRITE) && (NetworkEvents.iErrorCode[FD_WRITE_BIT] != 0)) {
                NetWorking::err_display(NetworkEvents.iErrorCode[FD_WRITE_BIT]);
                continue;
            }
        }*/

        //FD_CLOSE 이벤트 처리
        if (NetworkEvents.lNetworkEvents & FD_CLOSE) {
            if (NetworkEvents.iErrorCode[FD_CLOSE_BIT] != 0)
                NetWorking::err_quit("NetworkEvents.iErrorCode[FD_CLOSE_BIT]");
            if (NetWorking::GetSocketInfo(i)->GetLoby_Data()->Type == 1) {
                Room::DeleteHost(NetWorking::GetSocketInfo(i)->GetLoby_Data()->RoomNumber);
            }
            else if (NetWorking::GetSocketInfo(i)->GetLoby_Data()->Type == 3) {
                Room::DeleteHost(NetWorking::GetSocketInfo(i)->GetLoby_Data()->RoomNumber);
            }
            else {
                Room::DeleteClient(NetWorking::GetSocketInfo(i)->GetLoby_Data()->RoomNumber);
            }
            NetWorking::RemoveSocketInfo(i);
        }
    }
    //윈속 종료
    WSACleanup();
    return 0;
}