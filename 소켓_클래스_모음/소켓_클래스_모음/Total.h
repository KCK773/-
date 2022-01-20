#include <iostream>
#include <stdint.h>
#include <WinSock2.h>
#define WIN32_LEAN_AND_MEAN
#include<Windows.h>
#include<WS2tcpip.h>
#include<memory>

using namespace std;


#include "SocketAddress.h"
#include "SocketAddressFactory.h"
#include "UDPSocket.h"
#include "SocketUtil.h"