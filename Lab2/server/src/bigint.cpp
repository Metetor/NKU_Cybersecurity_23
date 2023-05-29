#include"bigint.h"
#include<stdint.h>
//默认构造函数,成员数据清0
BigInt::BigInt()
{
	for (int i = 0; i < MAXSIZE; i++)
		data[i] = 0;
	pn = true;
	len = 0;
}

//用int初始化大数
BigInt::BigInt(const int& a)
{
	for (int i = 0; i < MAXSIZE; i++)
		data[i] = 0;
	data[0] = a;
	if (a >= 0)
		pn = true;
	else
		pn = false;
	len = 1;
}

//用大数给大数赋值
BigInt::BigInt(const BigInt& a)
{
	for (int i = 0; i < MAXSIZE; i++)
		data[i] = a.data[i];
	pn = a.pn;
	len = a.len;
}

//用大数给大数赋值
void BigInt::operator= (const BigInt& a)
{
	for (int i = 0; i < MAXSIZE; i++)
		data[i] = a.data[i];
	pn = a.pn;
	len = a.len;
}

//比较两个大数的大小,a<b,返回真,否则返回假
bool operator< (const BigInt& a, const BigInt& b)
{
	for (int i = MAXSIZE - 1; i > 0; i--)
	{
		if (a.data[i] < b.data[i])
			return true;
		if (a.data[i] > b.data[i])
			return false;
	}
	return a.data[0] < b.data[0];
}

//比较两个大数的大小,a>b,返回真,否则返回假
bool operator> (const BigInt& a, const BigInt& b)
{
	for (int i = MAXSIZE - 1; i >= 0; i--)
	{
		if (a.data[i] > b.data[i])
			return true;
		if (a.data[i] < b.data[i])
			return false;
	}
	return false;
}

//判断两个大数是否相等,相等返回真,否则返回假
bool operator== (const BigInt& a, const BigInt& b)
{
	for (int i = 0; i < MAXSIZE; i++)
		if (a.data[i] != b.data[i])
			return false;
	return true;
}

//判断一个大数和一个int值是否相等,相等返回真,否则返回假
bool operator== (const BigInt& a, const int& b)
{
	for (int i = 1; i < a.GetLength(); i++)
		if (a.data[i] != 0)
			return false;
	return a.data[0] == b;
}

//计算两个大数的和,采用竖式相加法
BigInt operator+ (const BigInt& a, const BigInt& b)
{
	BigInt result;
	//64位数据,存放每两位数相加的临时和
	uint64_t sum;
	//carry为进位标志,sub为当两数符号相异时,存放每两位数相减的临时差
	unsigned int carry = 0, sub;
	//取a,b中长度较长的长度
	int length = (a.GetLength() >= b.GetLength() ? a.GetLength() : b.GetLength());

	//当两数符号相同时,进行加法运算
	if (a.pn == b.pn)
	{
		//每一位进行竖式相加
		for (int i = 0; i < length; i++)
		{
			sum = (uint64_t)a.data[i] + b.data[i] + carry;
			result.data[i] = (unsigned int)sum;
			//sum的高位为进位
			carry = (sum >> 32);
		}

		result.pn = a.pn;
		return result;
	}

	//两数符号不同时,进行减法运算
	else
	{
		BigInt tmp1, tmp2;

		//取出a,b中绝对值较大的作为被减数
		if (a < b)
		{
			tmp1 = b;
			tmp2 = a;
		}
		else
		{
			tmp1 = a;
			tmp2 = b;
		}

		//每一位进行竖式减
		for (int i = 0; i < length; i++)
		{
			sub = tmp2.data[i] + carry;
			if (tmp1.data[i] >= sub)
			{
				result.data[i] = tmp1.data[i] - sub;
				carry = 0;
			}
			else
			{
				//借位减
				result.data[i] = (uint64_t)tmp1.data[i] + (1 << 32) - sub;
				carry = 1;
			}
		}
		result.pn = tmp1.pn;
		result.len = result.GetLength();
		return result;
	}
}

//计算两个大数的差,采用竖式相减法
BigInt operator- (const BigInt& a, const BigInt& b)
{
	BigInt result;
	//64位数据,存放每两位数相加的临时和
	uint64_t sum;
	//carry为进位标志,sub为当两数符号相异时,存放每两位数相减的临时差
	unsigned int c = 0, sub;

	//符号相同时,进行减法运算
	if (a.pn == b.pn)
	{
		BigInt tmp1, tmp2;

		//取出a,b中绝对值较大的作为被减数
		if (a < b)
		{
			tmp1 = b;
			tmp2 = a;
			tmp1.pn = !tmp1.pn;
		}
		else
		{
			tmp1 = a;
			tmp2 = b;
		}

		//每一位进行竖式减
		for (int i = 0; i < MAXSIZE; i++)
		{
			sub = tmp2.data[i] + c;
			if (tmp1.data[i] >= sub)
			{
				result.data[i] = tmp1.data[i] - sub;
				c = 0;
			}
			else
			{
				//借位减
				result.data[i] = (uint64_t)tmp1.data[i] + (1 << 32) - sub;
				c = 1;
			}
		}
		result.pn = tmp1.pn;
		result.len = result.GetLength();
		return result;
	}

	//两数符号不同时,进行加法运算
	else
	{
		//每一位进行竖式相加
		for (int i = 0; i < MAXSIZE; i++)
		{
			sum = (uint64_t)a.data[i] + b.data[i] + c;
			result.data[i] = (unsigned int)sum;
			//sum的高位为进位
			c = (sum >> 32);
		}
		result.pn = a.pn;
		result.len = result.GetLength();
		return result;
	}
}

//大数减一个int数
BigInt operator- (const BigInt& a, const int& b)
{
	BigInt tmp(b);
	BigInt result = a - tmp;
	result.len = result.GetLength();
	return result;
}


//大数乘以一个INT数
BigInt operator* (const BigInt& a, const unsigned int& b)
{
	BigInt result;
	//存放B乘以A的每一位的临时积
	uint64_t sum;
	//存放进位
	unsigned int c = 0;

	for (int i = 0; i < MAXSIZE; i++)
	{
		sum = ((uint64_t)a.data[i]) * b + c;
		result.data[i] = (unsigned int)sum;
		//进位在SUM的高位中
		c = (sum >> 32);
	}
	result.pn = a.pn;
	result.len = result.GetLength();
	return result;
}

//大数相乘,采用竖式乘
BigInt operator* (const BigInt& a, const BigInt& b)
{
	//last存放竖式上一行的积,temp存放当前行的积
	BigInt result, last, tmp;
	//sum存放当前行带进位的积
	uint64_t sum;
	//存放进位
	unsigned int c;

	//进行竖式乘
	for (int i = 0; i < b.GetLength(); i++)
	{
		c = 0;
		//B的每一位与A相乘
		for (int j = 0; j < a.GetLength() + 1; j++)
		{
			sum = ((uint64_t)a.data[j]) * (b.data[i]) + c;
			if ((i + j) < MAXSIZE)
				tmp.data[i + j] = (unsigned int)sum;
			c = (sum >> 32);
		}
		result = (tmp + last);
		last = result;
		tmp.Clear();
	}

	//判断积的符号
	if (a.pn == b.pn)
		result.pn = true;
	else
		result.pn = false;
	result.len = result.GetLength();
	return result;
}

//大数除,采用试商除法,采用二分查找法优化
BigInt operator/ (const BigInt& a, const BigInt& b)
{
	//mul为当前试商,low,high为二分查找试商时所用的标志
	unsigned int mul, low, high;
	//sub为除数与当前试商的积,subsequent为除数与下一试商的积
	//dividend存放临时被除数
	BigInt dividend, quotient, sub, subsequent;
	int lengtha = a.GetLength(), lengthb = b.GetLength();

	//如果被除数小于除数,直接返回0
	if (a < b)
	{
		if (a.pn == b.pn)
			quotient.pn = true;
		else
			quotient.pn = false;
		return quotient;
	}

	//把被除数按除数的长度从高位截位
	int i;
	for (i = 0; i < lengthb; i++)
		dividend.data[i] = a.data[lengtha - lengthb + i];

	for (i = lengtha - lengthb; i >= 0; i--)
	{
		//如果被除数小于除数,再往后补位
		if (dividend < b)
		{
			for (int j = lengthb; j > 0; j--)
				dividend.data[j] = dividend.data[j - 1];
			dividend.data[0] = a.data[i - 1];
			continue;
		}

		low = 0;
		high = 0xffffffff;

		//二分查找法查找试商
		while (low < high)
		{
			mul = (((uint64_t)high) + low) / 2;
			sub = (b * mul);
			subsequent = (b * (mul + 1));

			if (((sub < dividend) && (subsequent > dividend)) || (sub == dividend))
				break;
			if (subsequent == dividend)
			{
				mul++;
				sub = subsequent;
				break;
			}
			if ((sub < dividend) && (subsequent < dividend))
			{
				low = mul;
				continue;
			}
			if ((sub > dividend) && (subsequent > dividend))
			{
				high = mul;
				continue;
			}

		}

		//试商结果保存到商中去
		quotient.data[i] = mul;
		//临时被除数变为被除数与试商积的差
		dividend = dividend - sub;

		//临时被除数往后补位
		if ((i - 1) >= 0)
		{
			for (int j = lengthb; j > 0; j--)
				dividend.data[j] = dividend.data[j - 1];
			dividend.data[0] = a.data[i - 1];
		}
	}

	//判断商的符号
	if (a.pn == b.pn)
		quotient.pn = true;
	else
		quotient.pn = false;
	quotient.len = quotient.GetLength();
	return quotient;
}

//大数求模运算,与除法运算类似
BigInt operator% (const BigInt& a, const BigInt& b)
{
	unsigned int mul, low, high;
	BigInt dividend, quotient, sub, subsequent;
	int lengtha = a.GetLength(), lengthb = b.GetLength();

	//如果被除数小于除数,返回被除数为模
	if (a < b)
	{
		dividend = a;
		//余数的商永远与被除数相同
		dividend.pn = a.pn;
		return dividend;
	}

	//进行除法运算
	int i;
	for (i = 0; i < lengthb; i++)
		dividend.data[i] = a.data[lengtha - lengthb + i];

	for (i = lengtha - lengthb; i >= 0; i--)
	{
		if (dividend < b)
		{
			for (int j = lengthb; j > 0; j--)
				dividend.data[j] = dividend.data[j - 1];
			dividend.data[0] = a.data[i - 1];
			continue;
		}

		low = 0;
		high = 0xffffffff;

		while (low <= high)
		{
			mul = (((uint64_t)high) + low) / 2;
			sub = (b * mul);
			subsequent = (b * (mul + 1));

			if (((sub < dividend) && (subsequent > dividend)) || (sub == dividend))
				break;
			if (subsequent == dividend)
			{
				mul++;
				sub = subsequent;
				break;
			}
			if ((sub < dividend) && (subsequent < dividend))
			{
				low = mul;
				continue;
			}
			if ((sub > dividend) && (subsequent > dividend))
			{
				high = mul;
				continue;
			}
		}

		quotient.data[i] = mul;
		dividend = dividend - sub;
		if ((i - 1) >= 0)
		{
			for (int j = lengthb; j > 0; j--)
				dividend.data[j] = dividend.data[j - 1];
			dividend.data[0] = a.data[i - 1];
		}
	}

	//临时被除数即为所求模
	dividend.pn = a.pn;
	dividend.len = dividend.GetLength();
	return dividend;
}
//产生一个随机大数,if small=false 大数的LENGTH为SIZE的1/4;small=true,大数的LENGTH为SIZE的1/8
void BigInt::Random(int size)
{
	if(size>MAXSIZE)
	{
		perror("size illegal");
		exit(0);
	}
	for(int i=0;i<size;i++)
	{
		data[i]=(rand() << 17) + (rand() << 2) + (rand());
	}
	len = this->GetLength();
}

//将大数以16进制显示到屏幕上
void BigInt::display() const
{
	unsigned int temp, result;
	unsigned int an = 0xf0000000;

	for (int i = len - 1; i >= 0; i--)
	{
		temp = data[i];
		//大数的每一位数字转换成16进制输出
		for (int j = 0; j < 8; j++)
		{
			result = temp & an;
			result = (result >> 28);
			temp = (temp << 4);
			if (result >= 0 && result <= 9)
				cout << result;
			else
			{
				switch (result)
				{
				case 10:
					cout << "A";
					break;
				case 11:
					cout << "B";
					break;
				case 12:
					cout << "C";
					break;
				case 13:
					cout << "D";
					break;
				case 14:
					cout << "E";
					break;
				case 15:
					cout << "F";
					break;
				}
			}
		}
		cout << " ";
		if (i == len / 2)
			cout << endl;
	}
	cout << endl;
}

//将大数输出到输入输出流
void BigInt::Output(ostream& out) const
{
	unsigned int temp, result;
	unsigned int an = 0xf0000000;

	for (int i = len - 1; i >= 0; i--)
	{
		temp = data[i];
		//大数的每一位数字转换成16进制输出
		for (int j = 0; j < 8; j++)
		{
			result = temp & an;
			result = (result >> 28);
			temp = (temp << 4);
			if (result >= 0 && result <= 9)
				out << result;
			else
			{
				switch (result)
				{
				case 10:
					out << "A";
					break;
				case 11:
					out << "B";
					break;
				case 12:
					out << "C";
					break;
				case 13:
					out << "D";
					break;
				case 14:
					out << "E";
					break;
				case 15:
					out << "F";
					break;
				}
			}
		}
	}
	out << endl;
}

//重载输出操作符
ostream& operator<< (ostream& out, const BigInt& x)
{
	x.Output(out);
	return out;
}

//大数置0
void BigInt::Clear()
{
	for (int i = 0; i < MAXSIZE; i++)
		data[i] = 0;
}

//返回大数长度
inline int BigInt::GetLength() const
{
	int length = MAXSIZE;
	for (int i = MAXSIZE - 1; i >= 0; i--)
	{
		//第一位不为0即为LENGTH
		if (data[i] == 0)
			length--;
		else
			break;
	}
	return length;
}

//重载移位操作符,向右移N位
void BigInt::operator>> (const int& a)
{
	unsigned int bit;
	data[0] = (data[0] >> a);
	for (int i = 1; i < len; i++)
	{
		//先将每一位的低位移到BIT中
		bit = data[i] & 1;
		//再把BIT移到上一位的高位中
		bit = bit << (32 - a);;
		data[i - 1] = data[i - 1] | bit;
		data[i] = (data[i] >> a);
	}
	len = this->GetLength();
}

//判断大数和一个INT的大小
bool operator<= (const BigInt& a, const int& b)
{
	for (int i = 1; i < a.GetLength(); i++)
	{
		if (a.data[i] != 0)
			return false;
	}
	if (a.data[0] <= b)
		return true;
	else
		return false;
}


//快速幂运算——计算n的p次幂模m
//利用Montgomery算法，
BigInt Power(const BigInt& n, const BigInt& p, const BigInt& m)
{
	BigInt temp = p;
	BigInt base = n % m;
	BigInt result(1);

	//检测指数p的二进制形式的每一位
	while (!(temp <= 1))
	{
		//如果该位为1，则表示该位需要参与模运算
		if (temp.IsOdd())
		{
			result = (result * base) % m;
		}
		base = (base * base) % m;
		temp >> 1;
	}
	return (base * result) % m;
}



