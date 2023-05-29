#include<vector>
#include"bigint.h"
using std::vector;
#define BUFFERSIZE 10240
vector<int> pm(1000);
char sendBuf[BUFFERSIZE];
char recvBuf[BUFFERSIZE];
int nClientSocket;

pair<BigInt,BigInt> pk;
BigInt des_k;