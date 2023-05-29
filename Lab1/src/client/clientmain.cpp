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
		cout<<"[Input] ��������Ϣ:";
		while (msg == "")
			getline(cin, msg);
		string cipher = mydes.encrypt(msg, key);
		printf("\n��Ϣ���ܺ������Ϊ: ");
		for (auto c : cipher)
			printf("0x%x ", c);
		cout << endl;
		if (send(sockClient, cipher.c_str(), sizeof(sendBuffer), 0) == -1)
			perror("send");
		else
			printf("[Success] ���ͳɹ�\n");
	}
	//WSACleanup();
	system("pause");
	return 0;
}
