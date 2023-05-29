#include"DES.h"
#include"tool.h"
#include <iostream>
void leftShift(bitset<28>& data, int bit) {
	bitset<28> tmp = data;
	for (int i = 0; i < 28; i++)
	{
		data[i] = tmp[(i + bit) % 28];
	}
}

bitset<64> DES:: IP(const bitset<64> data)
{//��ʼ�û�
	bitset<64> res;
	for (int i = 0; i < 64; i++)
	{
		res[i] = data[IP_first[i] - 1];
	}
	return res;
}
bitset<64> DES:: IP_inverse(const bitset<64> data)
{
	bitset<64> res;
	//����ip���û�
	for (int i = 0; i < 64; i++)
	{
		res[i] = data[IP_last[i] - 1];
	}
	return res;
}
bitset<32> DES::Feistel(const bitset<32>& r, const bitset<48>& subkey)
{
	//����ִ����չ����
	bitset<48> expand;
	bitset<32> fe_res;
	for (int i = 0; i < 48; i++)
	{
		expand[i] = r[E[i] - 1];
	}
	//������Կ���
	expand = expand ^ subkey;
	//���飬S���û�
	for (int i = 0; i < 8; i++)
	{
		int head = i * 6;//ÿһ���һλ���±�
		int row = expand[head] * 2 + expand[head + 5];
		int col = expand[head + 1] * 8 + expand[head + 2] * 4 + expand[head + 3] * 2 + expand[head + 4];
		//cout << "row" << row << "col " << col << endl;
		//�û�
		for (int j = 0; j < 4; j++)
		{
			fe_res[i * 4 + j] = (S_BOX[i][row][col] >> (3 - j)) & 1;
		}
	}

	//P�û�
	bitset<32> tmp = fe_res;
	for (int i = 0; i < 32; i++)
	{
		fe_res[i] = tmp[P[i] - 1];
	}
	return fe_res;
};
void DES::gernerateSubkey(const bitset<64>& key) {
	bitset<56> cur;
	bitset<28> left;
	bitset<28> right;

	//pc_1�û�
	for (int i = 0; i < 56; i++)
	{
		cur[i] = key[PC_1[i] - 1];
		//cout << cur[i];
	}
	//cout << endl;
	for (int i = 0; i < 28; i++)
	{
		left[i] = cur[i];
	}
	for (int i = 0; i < 28; i++)
		right[i] = cur[i + 28];

	//ѭ������λ+ѹ���û�
	
	for (int round = 0; round < 16; round++)
	{
		leftShift(left, shiftBits[round]);
		leftShift(right, shiftBits[round]);
		//cout << "left" << round << ':';
		/*for (int j = 0; j < 28; j++)
			cout << left[j];
		cout << endl;
		cout << "right" << round << ':';
		for (int j = 0; j < 28; j++)
			cout << right[j];*/
			//�ϲ�
		for (int i = 0; i < 56; i++)
		{
			if (i < 28)
				cur[i] = left[i];
			else
				cur[i] = right[i - 28];
		}

		//ѹ���û�
		//cout << "��i�ֵ���ԿΪ:";
		for (int j = 0; j < 48; j++)
		{
			subKeys[round][j] = cur[PC_2[j] - 1];
			//cout<< subKeys[round][j];
		}
		//cout << endl;
	}
}
//�����Ƽ���
bitset<64> DES::encrypt(bitset<64>& plain, const bitset<64>& key) {
	bitset<32> left;
	bitset<32> right;
	bitset<32> nextLeft;
	bitset<64> cur;

	cur = IP(plain);
	for (int i = 0; i < 32; i++)
	{
		left[i] = cur[i];
	}
	for (int i = 0; i < 32; i++)
	{
		right[i] = cur[i + 32];
	}

	//16�ֵ���
	gernerateSubkey(key);
	/*for (int i = 0; i < 16; i++)
	{
		cout << "��" << i << "�ֵ���ԿΪ:" << endl;
		for (int j = 0; j < 48; j++)
			cout << subKeys[i][j];
		cout << endl;
	}*/
	for (int i = 0; i < 16; i++)
	{
		nextLeft = right;
		right = left ^ Feistel(right, subKeys[i]);//���
		/*cout << "f:";
		for (int i = 0; i < 32; i++)
			cout << right[i];
		cout << endl;*/
		left = nextLeft;
	}

	for (int i = 0; i < 32; i++)
		cur[i] = right[i];
	for (int i = 0; i < 32; i++)
		cur[i + 32] = left[i];
	return IP_inverse(cur);
}
// �����ƽ���
bitset<64> DES::decrypt(bitset<64>& plain, const bitset<64>& key) {

	bitset<32> left; // ��¼�ϰ벿��
	bitset<32> right; // ��¼�°벿��
	bitset<32> nextLeft; // ��Ϊ16�ֵ������м���ʱ����
	bitset<64> cur; // ��¼ÿһ���û��Ľ��

	// ��һ����IP��ʼ�û�
	cur = IP(plain);

	// ��ȡL��R
	for (int i = 0; i < 32; i++)
		left[i] = cur[i];
	for (int i = 0; i < 32; i++)
		right[i] = cur[i + 32];

	// �ڶ�����16�ֵ���T
	gernerateSubkey(key);//��������Կ
	for (int i = 0; i < 16; i++) {
		nextLeft = right;
		right = left ^ Feistel(right, subKeys[15 - i]); // ����Կ����˳�������ʱ�෴
		left = nextLeft;
	}

	// �������������û�
	for (int i = 0; i < 32; i++)
		cur[i] = right[i];
	for (int i = 0; i < 32; i++)
		cur[i + 32] = left[i];

	// ���Ĳ���IP_1���û�
	return IP_inverse(cur);
}
string DES:: encrypt(string msg, const bitset<64>& key)
{
	string cipher;
	int len = msg.size();
	unsigned int pad = 8 - len % 8;
	for (int i = len; i < len+pad; i++)
	{
		msg += (char)pad;
	}
	for (int i = 0; i < msg.size(); i += 8)
	{
		//ÿ64bitsһ��
		string tmp = msg.substr(i, i + 8);
		bitset<64> data = stob(tmp);
		//���ö����Ƽ���
		bitset<64> c = encrypt(data, key);
		cipher += btos(c);
	}
	return cipher;
}
string DES::decrypt(string cipher, const bitset<64>& key)
{
	string plain;
	int len = cipher.size();
	for (int i = 0; i < len; i += 8)
	{
		string tmp = cipher.substr(i, i + 8);
		bitset<64> data = stob(tmp);
		bitset<64> p = decrypt(data, key);
		plain += btos(p);
	}
	int pad = plain[plain.size() - 1];
	plain = plain.substr(0, plain.size() - pad);
	return plain;
}