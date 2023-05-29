#include<winsock.h>
#include<windows.h>
#include<bitset>
#pragma comment(lib,"ws2_32.lib")
#define IP_BUF_SIZE 129
using namespace std;
DWORD ClientIP = inet_addr("127.0.0.1");
DWORD ServerIP = inet_addr("127.0.0.2");
u_short ClientPort = htons(11111);
u_short ServerPort = htons(22222);
SOCKET sockClient;
SOCKET sockServer;
SOCKADDR_IN  addrCli;
SOCKADDR_IN addrSer;
char recvBuffer[1024];
unsigned char key_s[8];
char buf_ip[IP_BUF_SIZE];