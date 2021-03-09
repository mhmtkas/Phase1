#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "appCashier.h"
#include <WS2tcpip.h>
#include <winsock2.h>
#include <ostream>

#pragma comment(lib, "Ws2_32.lib")




void appIdleLoop(const unsigned char* cashierName);
int transferToServer();