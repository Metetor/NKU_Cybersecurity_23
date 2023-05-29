#ifndef __MYRSA_H__
#define __MYRSA_H__
#include"bigint.h"
#include"tool.h"
class myRSA{
    //公钥，密钥
    friend bool RabinMiller(const BigInt& n);
    //friend void genPrime(std:: vector<int> pm);
public:
    BigInt n,e,d;

    myRSA(){};
    void pTabScr(BigInt& n);//素数表筛查，产生一个待测奇数,不能被小于5000的素数整除
    BigInt GenPrime();
    void GenRSAKey();
    ~myRSA(){};
};

#endif