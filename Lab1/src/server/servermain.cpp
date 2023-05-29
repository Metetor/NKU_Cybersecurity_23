#include<iostream>
#include <Ws2tcpip.h> 
#include"DES.h"
#include"Init.h"
#include "tool.h"
using namespace std;
DES mydes;
bitset<64> key;
DWORD WINAPI handlerRequest(LPVOID lparam);
void WaitForClient()
{
	int len = sizeof(SOCKADDR);
	while (true)
	{
		SOCKET sock_clt= accept(sockServer, (SOCKADDR*)&addrCli, &len);

		if (sock_clt == INVALID_SOCKET)
		{
			cerr << "Failed to accept client!Error code:" << WSAGetLastError() << "\n";
			WSACleanup();
			system("pause");
			exit(1);
		}
		::InetNtop(addrCli.sin_family, &addrCli, buf_ip, IP_BUF_SIZE);
		cout << "A new client connected...IP address: " << buf_ip << ", port number: " << ::ntohs(addrCli.sin_port) << endl;
		HANDLE hthread = CreateThread(nullptr, 0, handlerRequest, LPVOID(sock_clt), 0, 0);
		if (hthread == NULL)
		{
			cerr << "Failed to create a new thread!Error code:" << WSAGetLastError() << "\n";
			WSACleanup();
			system("pause");
			exit(1);
		}
		CloseHandle(hthread);
	}

}
DWORD WINAPI handlerRequest(LPVOID lparam)
{
	char ip[129];
	InetNtop(addrCli.sin_family, &addrCli, ip, IP_BUF_SIZE);
	SOCKET sock_clt = (SOCKET)lparam;
	char buf_msg[102400];
	int ret_val = 0;
	do
	{
		memset(buf_msg, 0, sizeof(buf_msg));
		ret_val = recv(sock_clt, buf_msg, 102400, 0);
		if (ret_val > 0)
		{
			//printf("[%s]接收到消息(密文):", ip);
			//for (auto c : buf_msg)
			//	printf("0x%x ", c);
			//cout << endl;

			string cipher = buf_msg;
			printf("[%s]接收到消息(密文):", ip);
			for (auto c : cipher)
				printf("0x%x ", c);
			cout << endl;
			string plain = mydes.decrypt(cipher, key);
			if (plain == "exit")
			{
				cout << "[exit] Client requests to close the connection...\n";
				break;
			}
			//cout << plain << endl;
			printf("[%s] (明文): ", ip);
			cout << plain << endl;
		}
		else if (ret_val == 0)
			cout << "connection closed ...\n";
		else
		{
			cerr << "Failed to create a new thread!Error code:" << WSAGetLastError() << "\n";
			WSACleanup();
			system("pause");
			exit(1);
		}
	} while (ret_val > 0);
	ret_val = shutdown(sock_clt, 1);
	if (ret_val == SOCKET_ERROR)
	{
		cerr << "Failed to shutdown the client socket!Error code:" << GetLastError() << endl;
		closesocket(sock_clt);
		system("pause");
		return 1;
	}
	return 0;
};
int main()
{
	Init();
	key = stob((char*)key_s);
	//开始监听
	if (listen(sockServer, 10) == -1) {
		perror("listen");
	}
	WaitForClient();

	//while (1)
	//{
	//	SOCKET clientSock = accept(sockServer, (SOCKADDR*)&addrCli, &len);
	//	while (1)
	//	{
	//		memset(recvBuffer, 0, sizeof(recvBuffer));
	//		if(recv(clientSock, recvBuffer, sizeof(recvBuffer), 0)==-1)
	//			perror("recv");
	//		else
	//		{
	//			//开始解密
	//			char cipher[1024];
	//			memcpy(cipher, recvBuffer, sizeof(recvBuffer));
	//			string plain = mydes.decrypt(cipher,key);
	//			cout << plain << endl;
	//		}
	//	}
	//}
	return 0;
}