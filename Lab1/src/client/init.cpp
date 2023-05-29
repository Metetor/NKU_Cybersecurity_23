#include<iostream>
#include"init.h"
void gen(unsigned char key[8],int seed)
{
	srand(seed);
	for (int i = 0; i < 8; i++)
	{
		key[i] = (char)(rand()%256);
	}
}//生成64bit密钥
int WSAInit() {
	WORD version = MAKEWORD(2, 2);
	WSAData wsadata;
	int error;
	error = WSAStartup(version, &wsadata);
	if (error != 0)
	{
		switch (error)
		{
		case WSASYSNOTREADY:
			printf("WSASYSNOTREADY");
			break;
		case WSAVERNOTSUPPORTED:
			printf("WSAVERNOTSUPPORTED");
			break;
		case WSAEINPROGRESS:
			printf("WSAEINPROGRESS");
			break;
		case WSAEPROCLIM:
			printf("WSAEPROCLIM");
			break;
		}
		return -1;
	}
	return 0;
}
int SockInit()
{
	sockClient = socket(AF_INET, SOCK_STREAM, 0);
	addrCli.sin_family = AF_INET;
	addrCli.sin_port = ClientPort;
	addrCli.sin_addr.S_un.S_addr = ClientIP;

	sockServer = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	addrSer.sin_family = AF_INET;
	addrSer.sin_port = ServerPort;
	addrSer.sin_addr.S_un.S_addr = ServerIP;

	if (bind(sockClient, (SOCKADDR*)&addrCli, sizeof(SOCKADDR)) == -1)
		return 0;
	else
		return 1;
}

void Init()
{
	//生成DES密钥
	//输入随机数种子
	int seed;
	printf("请输入随机数种子:");
	std::cin >> seed;
	gen(key_s,seed);
	//printf("%s",key);
	if (!WSAInit())
		printf("[WSAInit,Success] WSA初始化成功\n");
	if (SockInit())
		printf("[SockInit,Success] Socket初始化成功\n");
	//初始化完成END
};