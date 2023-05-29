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
			//输出16进制加密结果
			//cout << "第" << i << "组加密结果为:";
			bitsetTohex(cipher);
			//cout << endl;
		}
		else
		{
			cipher = des.decrypt(txt, key);
			//cout << "第" << i << "组解密结果为:";
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
			perror("测试失败,请检查DES加密程序\n");
	}
	printf("经测试，DES加密解密未发现异常\n");
}
void test_des_2()
{

	string msg = "你好啊啊";
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
	string txt = "hellmydesworld我爱你!";
	bitset<64> key = stob((char*)cases[0].key);
	string cipher = mydes.encrypt(txt, key);
	string plain = mydes.decrypt(cipher, key);
	cout << plain;
}