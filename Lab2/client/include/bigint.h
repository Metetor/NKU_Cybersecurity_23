#ifndef __BIGINT_H__
#define __BIGINT_H__
#include <iostream>
#include <stdlib.h> 
using namespace std;

const int MAXSIZE = 64;
class BigInt {
	friend BigInt operator+ (const BigInt&, const BigInt&);
	friend BigInt operator- (const BigInt&, const BigInt&);
	friend BigInt operator- (const BigInt&, const int&);
	friend BigInt operator* (const BigInt&, const BigInt&);
	friend BigInt operator* (const BigInt&, const unsigned int&);
	friend BigInt operator% (const BigInt&, const BigInt&);
	friend BigInt operator/ (const BigInt&, const BigInt&);
	friend bool operator< (const BigInt&, const BigInt&);
	friend bool operator> (const BigInt&, const BigInt&);
	friend bool operator<= (const BigInt&, const int&);
	friend bool operator== (const BigInt&, const BigInt&);
	friend bool operator== (const BigInt&, const int&);
	friend ostream& operator<< (ostream&, const BigInt&);
	friend BigInt Power(const BigInt&, const BigInt&, const BigInt&);//计算幂

public:
	BigInt();
	BigInt(const int&);
	BigInt(const BigInt&);

	void operator= (const BigInt&);
	void operator= (const int& a) { Clear(); data[0] = a; }
	void operator>> (const int&);

	inline int GetLength() const;   //返回大数的长度
	bool GetPN() { return pn; }  //判断大数的正负 
	void Clear();  //大数清0
	//void Random(); //随机产生一个大数
	void Random(int size,int seed=1140);  //随机产生一个稍小的大数
	void display() const;
	void Output(ostream& out) const;
	bool IsOdd() const { return (data[0] & 1); }  //判断大数奇偶性

public:
	unsigned int data[MAXSIZE];
	bool pn;
	int len;
};


#endif