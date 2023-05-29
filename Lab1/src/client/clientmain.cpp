#include<iostream>
#include<string>
#include"DES.h"
#include"tool.h"
#include "test.h"
#include"init.h"
using namespace std;
int main()
{
	test_des_3();
	DES mydes;
	Init();
	bitset<64> key = stob((char*)key_s);
	if (connect(sockClient, (SOCKADDR*)&addrSer, sizeof(SOCKADDR)) == -1)
		perror("connect");
	else
		printf("[Connect] Connect to Server\n");
	while (1)
	{
		string msg;
		cout<<"[Input] 请输入消息:";
		while (msg == "")
			getline(cin, msg);
		string cipher = mydes.encrypt(msg, key);
		printf("\n消息加密后的密文为: ");
		for (auto c : cipher)
			printf("0x%x ", c);
		cout << endl;
		if (send(sockClient, cipher.c_str(), sizeof(sendBuffer), 0) == -1)
			perror("send");
		else
			printf("[Success] 发送成功\n");
	}
	//WSACleanup();
	system("pause");
	return 0;
}
