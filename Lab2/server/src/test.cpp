#include"myRSA.h"
#include"myDES.h"
#include"test.h"
void test_rsa()
{
    myRSA myrsa;
    myrsa.GenRSAKey();
    return ;
}

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
			cout << "第" << i << "组加密结果为:";
			bitsetTohex(cipher);
			cout << endl;
		}
		else
		{
			cipher = des.decrypt(txt, key);
			cout << "第" << i << "组解密结果为:";
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
			perror("测试失败,请检查DES加密程序\n");
	}
	printf("经测试,test_des_1加密解密未发现异常\n");
}
void test_des_2()
{

	string msg = "ilikedes";
	cout << "加密明文为:" << msg << endl;
	bitset<64> txt = stob(msg);
	cout << "对应二进制串:" << txt << endl;
	bitset<64> key = stob((char*)cases[0].key);
	cout << "加密密钥为:" << key << endl;
	bitset<64> cipher,plain;
	DES mydes;
	cipher = mydes.encrypt(txt, key);
	cout << "加密密文(16进制)为:";
	bitsetTohex(cipher);
	cout << endl;
	plain=mydes.decrypt(cipher, key);
	cout << "解密明文(16进制)为:"<<plain<<endl;
	string str = btos(plain);
	cout << "解密信息为:" << str << endl;
	//cout << str;
	printf("经测试，test_des_2加密解密未发现异常\n");
}
void test_des_3() {
	DES mydes;
	string txt = "aaaaaaaaaaaaaaaaaaaaaaaaaaa";
	cout << "加密明文为:" << txt << endl;
	bitset<64> key = stob((char*)cases[0].key);
	string cipher = mydes.encrypt(txt, key);
	cout << "加密密钥为:" << key << endl;
	cout << "加密密文(16进制)为:";
	for (auto c : cipher)
		printf("0x%x", c);
	cout << endl;
	string plain = mydes.decrypt(cipher, key);
	cout << "解密信息为:" << plain << endl;
	printf("经测试，test_des_3加密解密未发现异常\n");
}