#ifndef __CHAT_H__
#define __CHAT_H__
typedef long unsigned int size_t;
size_t TotalRecv(int s, void *buf, size_t len, int flags);
void SecretChat(int nSock,char *pRemoteName);
void KeyInit();
void Init();



#endif