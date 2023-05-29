#include <iostream>
#include"test.h"
#include"DES.h"
#include"tool.h"
void test_des_1() {
	for (int i = 0; i < 20; i++)
	{
		DES des;
		bitset<64> txt = stob((char*)cases[i].txt);
		bitset<64> key = stob((char*)cases[i].key);
		char* out;
		bitset<64> cipher;
		if (cases[i].mode)
		{
			cipher = des.encrypt(txt, key);
			//���16���Ƽ��ܽ��
			cout << "��" << i << "����ܽ��Ϊ:";
			bitsetTohex(cipher);
			cout << endl;
		}
		else
		{
			cipher = des.decrypt(txt, key);
			cout << "��" << i << "����ܽ��Ϊ:";
			bitsetTohex(cipher);
			cout << endl;
		}
		bool flag = 1;
		bitset<64> bout = stob((char*)cases[i].out);
		for (int i = 0; i < 64; i++)
		{
			if (cipher[i] != bout[i])
			{
				flag = 0;
				break;
			}
		}
		if (!flag)
			perror("����ʧ��,����DES���ܳ���\n");
	}
	printf("�����ԣ�test_des_1���ܽ���δ�����쳣\n");
}
void test_des_2()
{

	string msg = "ilikedes";
	cout << "��������Ϊ:" << msg << endl;
	bitset<64> txt = stob(msg);
	cout << "��Ӧ�����ƴ�:" << txt << endl;
	bitset<64> key = stob((char*)cases[0].key);
	cout << "������ԿΪ:" << key << endl;
	bitset<64> cipher,plain;
	DES mydes;
	cipher = mydes.encrypt(txt, key);
	cout << "��������(16����)Ϊ:";
	bitsetTohex(cipher);
	cout << endl;
	plain=mydes.decrypt(cipher, key);
	cout << "��������(16����)Ϊ:"<<plain<<endl;
	string str = btos(plain);
	cout << "������ϢΪ:" << str << endl;
	//cout << str;
	printf("�����ԣ�test_des_2���ܽ���δ�����쳣\n");
}
void test_des_3() {
	DES mydes;
	string txt = "aaaaaaaaaaaaaaaaaaaaaaaaaaa";
	cout << "��������Ϊ:" << txt << endl;
	bitset<64> key = stob((char*)cases[0].key);
	string cipher = mydes.encrypt(txt, key);
	cout << "������ԿΪ:" << key << endl;
	cout << "��������(16����)Ϊ:";
	for (auto c : cipher)
		printf("0x%x", c);
	cout << endl;
	string plain = mydes.decrypt(cipher, key);
	cout << "������ϢΪ:" << plain << endl;
	printf("�����ԣ�test_des_3���ܽ���δ�����쳣\n");
}