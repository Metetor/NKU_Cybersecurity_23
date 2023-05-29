#ifndef __TOOL_H__
#define __TOOL_H__
#include<vector>
#include<bitset>
#include"bigint.h"
using std::vector;
using std::bitset;
//求两个大数的最大公约数,采用辗转相除法
BigInt gcd(const BigInt& m, const BigInt& n);

//用扩展欧几里德算法求乘法模逆
BigInt Extended_gcd(const BigInt& a, const BigInt& b, BigInt& x, BigInt& y);

//对大奇数n进行RabinMiller检测
//bool RabinMiller(const BigInt& n);

bool isPrime(int n);
void genPrime(vector<int>& pm);
bitset<64> stob(char s[8]);
bitset<64> stob(string s8);
string btos(bitset<64> bits);
void bitsetTohex(bitset<64> binset);
#endif