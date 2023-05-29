#include<vector>
#include"bigint.h"
using std::vector;
#define BUFFERSIZE 10240
vector<int> pm(1000);
char sendBuf[BUFFERSIZE];
char recvBuf[BUFFERSIZE];
int nServSocket, nClientSocket;
pair<BigInt,BigInt> pk;//RSA公钥
pair<BigInt,BigInt> sk;//RSA私钥
BigInt des_k;//des对话密钥