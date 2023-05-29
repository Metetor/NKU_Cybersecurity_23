#include<cmath>
#include "tool.h"

//求两个大数的最大公约数,采用辗转相除法
BigInt gcd(const BigInt& m, const BigInt& n)
{
	if (n == 0)
		return m;
	else
		return gcd(n, m % n);
}

//用扩展欧几里德算法求乘法模逆
BigInt Extended_gcd(const BigInt& a, const BigInt& b, BigInt& x, BigInt& y)
{
	BigInt t, d;
	//如果一个操作数为零则无法进行除法运算
	if (b == 0)
	{
		x = 1;
		y = 0;
		return a;
	}
	d = Extended_gcd(b, a % b, x, y);
	t = x;
	x = y;
	y = t - ((a / b) * y);
	return d;
}


bool isPrime(int n)
{
    if (n < 2) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    int foo = (int)sqrt(n);
    for (int i = 3; i <= foo; i += 2)
        if (n % i == 0) return false;
    return true;
};
void genPrime(vector<int>& pm)
{
    int base = 1;
    for (int i = 0; i < pm.size(); i++)
    {

        while (base++)
        {
            if (isPrime(base))
            {
                pm[i] = base;
                break;
            }
        }
    }
}

bitset<64> stob(char s[8])
{
	bitset<64> bits;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			bits[i * 8 + j] = (s[i] >> (7 - j)) & 1;
		}
	}
	return bits;
}
bitset<64> stob(string s8)
{
	bitset<64> bits;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			bits[i * 8 + j] = (s8[i] >> (7 - j)) & 1;
		}
	}
	return bits;
}
string btos(bitset<64> bits) {
	string res;
	uint8_t sum;
	for (int i = 0; i < 8; i++)
	{
		sum = 0;
		for (int j = 7; j >= 0; j--)
		{
			sum += bits[i * 8 + j] * pow(2, 7 - j);
		}
		res += (char)sum;
		//printf("0x%X ", sum);
	}
	return res;
};
void bitsetTohex(bitset<64> binset) {
	uint8_t sum;
	for (int i = 0; i < 8; i++)
	{
		sum = 0;
		for (int j = 7; j >= 0; j--)
		{
			sum += binset[i * 8 + j] * pow(2, 7 - j);
		}
		printf("0x%X ", sum);
	}
	return;
}