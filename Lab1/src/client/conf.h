#ifndef CONF_H
#define CONF_H
#include<winsock.h>
#pragma comment(lib,"ws2_32.lib")
#define MAXLEN 1024
extern DWORD ClientIP, ServerIP;
extern u_short ClientPort, ServerPort;
extern SOCKET sockClient, sockServer;
extern SOCKADDR_IN addrCli, addrSer;
extern char sendBuffer[1024];
extern unsigned char key_s[8];
#endif // !CONF_H

