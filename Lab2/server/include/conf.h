#ifndef __CONF_H__
#define __CONF_H__
#include<vector>
#define BUFFERSIZE 10240
using std::vector;
extern vector<int> pm;

extern char strSocketBuffer[BUFFERSIZE];
extern char strDecryBuffer[BUFFERSIZE];

extern int nServSocket, nClientSocket;

#endif