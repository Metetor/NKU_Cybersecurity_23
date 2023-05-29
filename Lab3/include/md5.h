#ifndef __MD5_H__
#define __MD5_H__
#include<sys/types.h>
#include<string>
#include<cstring>
#include<iostream>
#include<string.h>

using std::string;
using std::ifstream;

typedef unsigned char BYTE;
typedef unsigned long DWORD;

#define S11 7
#define S12 12
#define S13 17
#define S14 22
#define S21 5
#define S22 9
#define S23 14
#define S24 20
#define S31 4
#define S32 11
#define S33 16
#define S34 23
#define S41 6
#define S42 10
#define S43 15
#define S44 21

#define F(x,y,z) (((x)&(y))|((~x)&(z)))
#define G(x,y,z) (((x)&(z))|((y)&(~z)))
#define H(x,y,z) ((x)^(y)^(z))
#define I(x,y,z) ((y)^((x)|(~z)))
#define ROTATE_LEFT(x,n) (((x)<<(n))|((x)>>(32-(n))))
#define FF(a,b,c,d,x,s,ac) { a+=F(b,c,d)+x+ac; a=ROTATE_LEFT(a,s); a+=b;}
#define GG(a,b,c,d,x,s,ac) { a+=G(b,c,d)+x+ac; a=ROTATE_LEFT(a,s); a+=b;}
#define HH(a,b,c,d,x,s,ac) { a+=H(b,c,d)+x+ac; a=ROTATE_LEFT(a,s); a+=b;}
#define II(a,b,c,d,x,s,ac) { a+=I(b,c,d)+x+ac; a=ROTATE_LEFT(a,s); a+=b;}


class MD5
{
public:
    MD5();
    MD5(const string &str);
    MD5(ifstream &in);
    //对给定长度的输入流进行MD5运算
    void Update(const void* input,size_t length);
    //对给定长度的字符串进行MD5运算
    void Update(const string &str);
    void Update(ifstream &in);//对文件中的内容进行MD5运算
    const BYTE* GetDigest();
    string Tostring();//将MD5摘要以字符串形式输出
    void Reset();
private:
    //对给定长度的字节流进行MD5运算
    void Update(const BYTE* input,size_t length);
    void Stop();//用于终止摘要计算过程，输出摘要
    void Transform(const BYTE block[64]);//对消息分组进行MD5运算
    //将双字流转换为字节流
    void Encode(const DWORD *input,BYTE *output,size_t length);
    //将字节流转换为双字流
    void Decode(const BYTE *input,DWORD *output,size_t length);
    //将字节流按照十六进制字符串输出
    string BytesToHexString(const BYTE *input,size_t length);
private:
    DWORD state[4];//用于表示4个初始向量
    DWORD count[2];//用于计数，count[0]表示低位，count[1]表示高位
    BYTE buffer_block[64];//用于保存计算过程中按块划分后剩下的比特流
    BYTE digest[16]; //用于保存128比特长度的摘要
    bool is_finished;//用于标志摘要计算过程是否结束

    static const BYTE padding[64];//用于保存消息后面填充的数据块
    static const char hex[16];//用于保存16进制的字符
};

#endif