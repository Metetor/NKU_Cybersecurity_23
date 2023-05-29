#include"myDES.h"
#include"bigint.h"
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
{//初始置换
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
	//构造ip逆置换
	for (int i = 0; i < 64; i++)
	{
		res[i] = data[IP_last[i] - 1];
	}
	return res;
}
bitset<32> DES::Feistel(const bitset<32>& r, const bitset<48>& subkey)
{
	//首先执行扩展操作
	bitset<48> expand;
	bitset<32> fe_res;
	for (int i = 0; i < 48; i++)
	{
		expand[i] = r[E[i] - 1];
	}
	//与子密钥异或
	expand = expand ^ subkey;
	//分组，S盒置换
	for (int i = 0; i < 8; i++)
	{
		int head = i * 6;//每一组第一位的下标
		int row = expand[head] * 2 + expand[head + 5];
		int col = expand[head + 1] * 8 + expand[head + 2] * 4 + expand[head + 3] * 2 + expand[head + 4];
		//cout << "row" << row << "col " << col << endl;
		//置换
		for (int j = 0; j < 4; j++)
		{
			fe_res[i * 4 + j] = (S_BOX[i][row][col] >> (3 - j)) & 1;
		}
	}

	//P置换
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

	//pc_1置换
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

	//循环左移位+压缩置换
	
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
			//合并
		for (int i = 0; i < 56; i++)
		{
			if (i < 28)
				cur[i] = left[i];
			else
				cur[i] = right[i - 28];
		}

		//压缩置换
		//cout << "第i轮的密钥为:";
		for (int j = 0; j < 48; j++)
		{
			subKeys[round][j] = cur[PC_2[j] - 1];
			//cout<< subKeys[round][j];
		}
		//cout << endl;
	}
}
//二进制加密
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

	//16轮迭代
	gernerateSubkey(key);
	/*for (int i = 0; i < 16; i++)
	{
		cout << "第" << i << "轮的密钥为:" << endl;
		for (int j = 0; j < 48; j++)
			cout << subKeys[i][j];
		cout << endl;
	}*/
	for (int i = 0; i < 16; i++)
	{
		nextLeft = right;
		right = left ^ Feistel(right, subKeys[i]);//异或
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
// 二进制解密
bitset<64> DES::decrypt(bitset<64>& plain, const bitset<64>& key) {

	bitset<32> left; // 记录上半部分
	bitset<32> right; // 记录下半部分
	bitset<32> nextLeft; // 作为16轮迭代的中间临时变量
	bitset<64> cur; // 记录每一步置换的结果

	// 第一步：IP初始置换
	cur = IP(plain);

	// 获取L和R
	for (int i = 0; i < 32; i++)
		left[i] = cur[i];
	for (int i = 0; i < 32; i++)
		right[i] = cur[i + 32];

	// 第二步：16轮迭代T
	gernerateSubkey(key);//生成子密钥
	for (int i = 0; i < 16; i++) {
		nextLeft = right;
		right = left ^ Feistel(right, subKeys[15 - i]); // 子密钥调度顺序与加密时相反
		left = nextLeft;
	}

	// 第三步：交换置换
	for (int i = 0; i < 32; i++)
		cur[i] = right[i];
	for (int i = 0; i < 32; i++)
		cur[i + 32] = left[i];

	// 第四步：IP_1逆置换
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
		//每64bits一组
		string tmp = msg.substr(i, i + 8);
		bitset<64> data = stob(tmp);
		//调用二进制加密
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