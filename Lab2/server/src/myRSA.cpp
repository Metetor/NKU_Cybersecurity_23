#include"conf.h"
#include"tool.h"
#include"myRSA.h"

//对大奇数n进行RabinMiller检测
bool RabinMiller(const BigInt& n)
{
	BigInt r, a, y;
	unsigned int s, j;
	r = n - 1;
	s = 0;

	while (!r.IsOdd())
	{
		s++;
		r >> 1;
	}

	//随机产生一个小于N-1的检测数a
	a.Random(8);

	//y = a的r次幂模n
	y = Power(a, r, n);

	//检测J=2至J<S轮
	if ((!(y == 1)) && (!(y == (n - 1))))
	{
		j = 1;
		while ((j <= s - 1) && (!(y == (n - 1))))
		{
			y = (y * y) % n;
			if (y == 1)
				return false;
			j++;
		}
		if (!(y == (n - 1)))
			return false;
	}
	return true;
}
//素数表筛查，产生一个待测奇数,不能被小于5000的素数整除
void myRSA::pTabScr(BigInt& n)
{
	int i = 0;
	BigInt divisor;
	const int length = 1000;
	while (i != length)
	{
        
		n.Random(16);
		while (!n.IsOdd())
			n.Random(16);
		i = 0;
		for (; i < length; i++)
		{
			divisor = pm[i];
			if ((n % divisor) == 0)
				break;
		}
        
	}
}
//产生一个素数
BigInt myRSA::GenPrime()
{
	BigInt n;
	int i = 0;

	//无限次循环，不断产生素数，直到i==5时（通过五轮RabinMiller测试）才会跳出while循环
	while (i < 5)
	{
		cout << "产生待测大奇数：" << endl;
		pTabScr(n);
        cout<<"ptabscr end!\n";
		n.display();

		i = 0;
		//进行五轮RABINMILLER测试,五轮全部通过则素数合格
		for (; i < 5; i++)
		{
			if (!RabinMiller(n))
			{
				cout << "RABINMILLER测试失败" << endl;
				break;
			}
			cout << "RABINMILLER测试通过" << endl;
		}
	}
	return n;
}
void myRSA::GenRSAKey() 
{
    //BigInt d;
	printf("生成RSA公钥密钥\n");
	genPrime(pm);
    cout<<pm[999]<<endl;
	//产生大素数
	printf("开始生成大素数p\n");
	BigInt p = GenPrime();
	p.display();

	BigInt q = GenPrime();
	q.display();
	
	/*printf("公钥n=p*q\n");*/

	n = p * q;

	BigInt t = (p - 1) * (q - 1);
	//y用于参与扩展欧几里得运算，存储t模e的乘法逆元
	BigInt y;

	BigInt temp;
	while (1)
	{
		//产生与t互质的e
		e.Random(16);
		while (!(gcd(e, t) == 1))
		{
			e.Random(16);
		}

		//用扩展欧几里德算法试图求出e模t的乘法逆元
		temp = Extended_gcd(e, t, d, y);

		//e*d模t结果为1，说明d确实是e模t的乘法逆元
		temp = (e * d) % t;
		if (temp == 1)
			break;
		//否则重新生成e
	}
}