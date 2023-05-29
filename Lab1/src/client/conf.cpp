#include<winsock.h>
#include<windows.h>
#pragma comment(lib,"ws2_32.lib")
DWORD ClientIP = inet_addr("127.0.0.1");
DWORD ServerIP = inet_addr("127.0.0.2");
u_short ClientPort = htons(11111);
u_short ServerPort = htons(22222);
SOCKET sockClient;
SOCKET sockServer;
SOCKADDR_IN  addrCli;
SOCKADDR_IN addrSer;
char sendBuffer[1024];
unsigned char key_s[8];
