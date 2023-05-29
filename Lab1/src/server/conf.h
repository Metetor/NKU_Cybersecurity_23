#ifndef __CONF_H__
#define __CONF_H__
#include<winsock.h>
#pragma comment(lib,"ws2_32.lib")
#define MAXLEN 1024
#define IP_BUF_SIZE 129
extern DWORD ClientIP, ServerIP;
extern u_short ClientPort, ServerPort;
extern SOCKET sockClient, sockServer;
extern SOCKADDR_IN addrCli, addrSer;
extern char recvBuffer[1024];
extern unsigned char key_s[8];
extern char buf_ip[IP_BUF_SIZE];
#endif // !__CONF_H__

