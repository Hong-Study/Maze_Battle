#pragma once
#include <memory>

using BYTE = unsigned char;
using int8 = __int8;
using int16 = __int16;
using int32 = __int32;
using int64 = __int64;
using uint8 = unsigned __int8;
using uint16 = unsigned __int16;
using uint32 = unsigned __int32;
using uint64 = unsigned __int64;

using SessionRef = std::shared_ptr<class Session>;
using ServiceRef = std::shared_ptr<class Service>;
using ServerServiceRef = std::shared_ptr<class ServerService>;
using ClientServiceRef = std::shared_ptr<class ClientService>;
