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
			//cout << "��" << i << "����ܽ��Ϊ:";
			bitsetTohex(cipher);
			//cout << endl;
		}
		else
		{
			cipher = des.decrypt(txt, key);
			//cout << "��" << i << "����ܽ��Ϊ:";
			bitsetTohex(cipher);
			//cout << endl;
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
		/*if (flag)
			cout << i << ":  true" << endl;
		else
			cout << i << ":  false" << endl;*/
		if (!flag)
			perror("����ʧ��,����DES���ܳ���\n");
	}
	printf("�����ԣ�DES���ܽ���δ�����쳣\n");
}
void test_des_2()
{

	string msg = "��ð���";
	bitset<64> txt = stob(msg);
	bitset<64> key = stob((char*)cases[0].key);
	bitset<64> cipher, plain;
	DES mydes;
	cipher = mydes.encrypt(txt, key);
	plain = mydes.decrypt(cipher, key);
	string str = btos(plain);
	cout << str;
}
void test_des_3() {
	DES mydes;
	string txt = "hellmydesworld�Ұ���!";
	bitset<64> key = stob((char*)cases[0].key);
	string cipher = mydes.encrypt(txt, key);
	string plain = mydes.decrypt(cipher, key);
	cout << plain;
}