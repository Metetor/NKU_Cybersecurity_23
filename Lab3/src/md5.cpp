#include"md5.h"
#include<fstream>

const BYTE MD5::padding[64] = {  
    0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  
};  
const char MD5::hex[16]={'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

MD5::MD5()
{
    count[0]=0;
    count[1]=0;
    Reset();
}

//从字符串构造函数，调用默认构造函数，然后更新摘要
MD5::MD5(const string &str)
{
    Reset();
    Update(str);
}

//从文件流构造函数，调用默认构造函数，然后读取文件内容并更新摘要
MD5::MD5(ifstream &in)
{
    if(in)
    {
        Update(in);
    }
}

void MD5::Transform(const BYTE block[64])
{
    //printf("Transform Entered\n");
    DWORD a=state[0],b=state[1],c=state[2],d=state[3],x[16];

    Decode(block,x,64);

    /* Round 1 */  
    FF (a, b, c, d, x[0], S11, 0xd76aa478); /* 1 */  
    FF (d, a, b, c, x[1], S12, 0xe8c7b756); /* 2 */  
    FF (c, d, a, b, x[2], S13, 0x242070db); /* 3 */  
    FF (b, c, d, a, x[3], S14, 0xc1bdceee); /* 4 */  
    FF (a, b, c, d, x[4], S11, 0xf57c0faf); /* 5 */  
    FF (d, a, b, c, x[5], S12, 0x4787c62a); /* 6 */  
    FF (c, d, a, b, x[6], S13, 0xa8304613); /* 7 */  
    FF (b, c, d, a, x[7], S14, 0xfd469501); /* 8 */  
    FF (a, b, c, d, x[8], S11, 0x698098d8); /* 9 */  
    FF (d, a, b, c, x[9], S12, 0x8b44f7af); /* 10 */  
    FF (c, d, a, b, x[10], S13, 0xffff5bb1); /* 11 */  
    FF (b, c, d, a, x[11], S14, 0x895cd7be); /* 12 */  
    FF (a, b, c, d, x[12], S11, 0x6b901122); /* 13 */  
    FF (d, a, b, c, x[13], S12, 0xfd987193); /* 14 */  
    FF (c, d, a, b, x[14], S13, 0xa679438e); /* 15 */  
    FF (b, c, d, a, x[15], S14, 0x49b40821); /* 16 */  
  
    /* Round 2 */  
    GG (a, b, c, d, x[ 1], S21, 0xf61e2562); /* 17 */  
    GG (d, a, b, c, x[ 6], S22, 0xc040b340); /* 18 */  
    GG (c, d, a, b, x[11], S23, 0x265e5a51); /* 19 */  
    GG (b, c, d, a, x[ 0], S24, 0xe9b6c7aa); /* 20 */  
    GG (a, b, c, d, x[ 5], S21, 0xd62f105d); /* 21 */  
    GG (d, a, b, c, x[10], S22,  0x02441453); /* 22 */  
    GG (c, d, a, b, x[15], S23, 0xd8a1e681); /* 23 */  
    GG (b, c, d, a, x[ 4], S24, 0xe7d3fbc8); /* 24 */  
    GG (a, b, c, d, x[ 9], S21, 0x21e1cde6); /* 25 */  
    GG (d, a, b, c, x[14], S22, 0xc33707d6); /* 26 */  
    GG (c, d, a, b, x[ 3], S23, 0xf4d50d87); /* 27 */  
    GG (b, c, d, a, x[ 8], S24, 0x455a14ed); /* 28 */  
    GG (a, b, c, d, x[13], S21, 0xa9e3e905); /* 29 */  
    GG (d, a, b, c, x[ 2], S22, 0xfcefa3f8); /* 30 */  
    GG (c, d, a, b, x[ 7], S23, 0x676f02d9); /* 31 */  
    GG (b, c, d, a, x[12], S24, 0x8d2a4c8a); /* 32 */  
  
    /* Round 3 */  
    HH (a, b, c, d, x[ 5], S31, 0xfffa3942); /* 33 */  
    HH (d, a, b, c, x[ 8], S32, 0x8771f681); /* 34 */  
    HH (c, d, a, b, x[11], S33, 0x6d9d6122); /* 35 */  
    HH (b, c, d, a, x[14], S34, 0xfde5380c); /* 36 */  
    HH (a, b, c, d, x[ 1], S31, 0xa4beea44); /* 37 */  
    HH (d, a, b, c, x[ 4], S32, 0x4bdecfa9); /* 38 */  
    HH (c, d, a, b, x[ 7], S33, 0xf6bb4b60); /* 39 */  
    HH (b, c, d, a, x[10], S34, 0xbebfbc70); /* 40 */  
    HH (a, b, c, d, x[13], S31, 0x289b7ec6); /* 41 */  
    HH (d, a, b, c, x[ 0], S32, 0xeaa127fa); /* 42 */  
    HH (c, d, a, b, x[ 3], S33, 0xd4ef3085); /* 43 */  
    HH (b, c, d, a, x[ 6], S34,  0x04881d05); /* 44 */  
    HH (a, b, c, d, x[ 9], S31, 0xd9d4d039); /* 45 */  
    HH (d, a, b, c, x[12], S32, 0xe6db99e5); /* 46 */  
    HH (c, d, a, b, x[15], S33, 0x1fa27cf8); /* 47 */  
    HH (b, c, d, a, x[ 2], S34, 0xc4ac5665); /* 48 */  
  
    /* Round 4 */  
    II (a, b, c, d, x[ 0], S41, 0xf4292244); /* 49 */  
    II (d, a, b, c, x[ 7], S42, 0x432aff97); /* 50 */  
    II (c, d, a, b, x[14], S43, 0xab9423a7); /* 51 */  
    II (b, c, d, a, x[ 5], S44, 0xfc93a039); /* 52 */  
    II (a, b, c, d, x[12], S41, 0x655b59c3); /* 53 */  
    II (d, a, b, c, x[ 3], S42, 0x8f0ccc92); /* 54 */  
    II (c, d, a, b, x[10], S43, 0xffeff47d); /* 55 */  
    II (b, c, d, a, x[ 1], S44, 0x85845dd1); /* 56 */  
    II (a, b, c, d, x[ 8], S41, 0x6fa87e4f); /* 57 */  
    II (d, a, b, c, x[15], S42, 0xfe2ce6e0); /* 58 */  
    II (c, d, a, b, x[ 6], S43, 0xa3014314); /* 59 */  
    II (b, c, d, a, x[13], S44, 0x4e0811a1); /* 60 */  
    II (a, b, c, d, x[ 4], S41, 0xf7537e82); /* 61 */  
    II (d, a, b, c, x[11], S42, 0xbd3af235); /* 62 */  
    II (c, d, a, b, x[ 2], S43, 0x2ad7d2bb); /* 63 */  
    II (b, c, d, a, x[ 9], S44, 0xeb86d391); /* 64 */  

    state[0]+=a;
    state[1]+=b;
    state[2]+=c;
    state[3]+=d;

    memset(x,0,sizeof(x));
};

void MD5::Update(const BYTE* input,size_t length)
{
    //printf("Update(BYTE) Entered\n");
    DWORD i,index,partLen;

    //设置停止标识
    is_finished=false;
    //计算buffer已经存放的字节数
    index=(DWORD)((count[0]>>3)&0x3f);

    //更新计数器count，将新数据流的长度加上计数器原有的值
    if((count[0]+=((DWORD)length<<3))<((DWORD)length<<3))
        count[1]++;
    count[1]+=((DWORD)length>>29);

    //求出buffer中剩余的长度
    partLen=64-index;
    //printf("Length:%d,partLen:%d",length,partLen);
    //将数据块逐块进行MD5运算
    if(length>=partLen)
    {
        memcpy(&buffer_block[index],input,partLen);
        Transform(buffer_block);

        for(i=partLen;i+63<length;i+=64)
            Transform(&input[i]);
        index=0;
    }else{
        i=0;
    }
    //将不足64字节的数据复制到buffer_block中
    memcpy(&buffer_block[index],&input[i],length-i);
};

void MD5::Encode(const DWORD *input, BYTE *output, size_t length) {
    for (size_t i = 0,j=0; j< length; i++,j+=4) {
        output[j] = (BYTE)(input[i] & 0xff);
        output[j + 1] = (BYTE)((input[i] >> 8) & 0xff);
        output[j + 2] = (BYTE)((input[i] >> 16) & 0xff);
        output[j + 3] = (BYTE)((input[i] >> 24) & 0xff);
    }
}


void MD5::Decode(const BYTE *input,DWORD *output,size_t length)
{
    for(size_t i=0,j=0;j<length;i++,j+=4)
    {
        output[i]=((DWORD)input[j])|((DWORD)input[j+1]<<8)|((DWORD)input[j+2]<<16)|((DWORD)input[j+3]<<24);
    }
}

const BYTE* MD5::GetDigest()
{
    if(!is_finished)
    {
        is_finished=true;
        Stop();
    }
    return digest;
}

string MD5::Tostring()
{
    return BytesToHexString(GetDigest(),16);
}

string MD5::BytesToHexString(const BYTE *input,size_t length)
{
    string str;
    str.reserve(length<<1);
    for(size_t i=0;i<length;i++)
    {
        int t=input[i];
        int a=t/16;
        int b=t%16;
        str.append(1,hex[a]);
        str.append(1,hex[b]);
    }
    return str;
}

void MD5::Reset()
{
    state[0] = 0x67452301;  
    state[1] = 0xefcdab89;  
    state[2] = 0x98badcfe;  
    state[3] = 0x10325476;  

    is_finished=false;
}

void MD5::Update(const void* input,size_t length)
{
    //Reset();
    //转换为BYTE*后调用私有Update函数
    this->Update((BYTE*)input,length);
}

void MD5:: Update(const string &str)
{
    //Reset();
    //printf("Update(string) Entered\n");
    this->Update((BYTE*)str.c_str(),str.length());
}

void MD5:: Update(ifstream &in)
{
    //Reset();
    //获取文件大小
    in.seekg(0, std::ios::end);
    int size = in.tellg();
    in.seekg(0, std::ios::beg);

    //创建BYTE数组
    BYTE *buffer=new BYTE[size];

    //读取文件内容到数组
    in.read((char*)buffer,size);

    in.close();

    this->Update(buffer,size);
}

void MD5::Stop(){
    //printf("Stop Entered\n");
    BYTE bytes[8];
    DWORD oldState[4];
    DWORD oldCount[2];
    DWORD index,padLen;
    memcpy(oldState,state,16);
    memcpy(oldCount,count,8);
    Encode(count,bytes,8);
    index=(DWORD)((count[0]>>3)&0x3f);
    padLen=(index<56)?(56-index):(120-index);
    Update(padding,padLen);
    Update(bytes,8);
    Encode(state,digest,16);

    memcpy(state,oldState,16);
    memcpy(count,oldCount,8);
    //memset(buffer_block,0,sizeof(buffer_block));
    //memset(count,0,sizeof(count));
    is_finished=true;
}