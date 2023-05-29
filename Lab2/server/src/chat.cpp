#include<iostream>
#include<cstring>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include"conf.h"
#include"chat.h"
#include"myRSA.h"
#include"myDES.h"
using std::cin;
bitset<64> key;
extern BigInt des_k;
void SecretChat(int nSock,char *pRemoteName,BigInt des_k)
{
    DES cDes;
    for(int i=0;i<2;i++)
    {
        for(int j=0;j<32;j++)
        {
            key[i * 2 + j] = (des_k.data[i] >> (31 - j)) & 1;
        }
    }
    pid_t nPid;
    nPid=fork();
    if(nPid!=0)
    {
        //recv thread
        extern char recvBuf[BUFFERSIZE];
        while(1)
        { 
            bzero(recvBuf,BUFFERSIZE);
            read(nSock,recvBuf,BUFFERSIZE);
            string cipher=recvBuf;
            printf("接收的密文消息为:\n");
            for(auto c:cipher)
            {
                printf("0x%x ",c);
            }
            printf("\n");
            string plain=cDes.decrypt(cipher,key);
            if(plain=="quit")
            {
                //退出
                printf("Quit\n");
                return;
            }
            std::cout<<"[recv from <"<<pRemoteName<<">]:"<<plain<<endl;
        } 
    }
    else
    {
        //send thread
        while(1){
            //send thread
            string plain;
            //printf("请输入消息:\n");
            while(plain=="")
            {
                getline(cin,plain);
            }
            string cipher=cDes.encrypt(plain,key);
            printf("发送的消息密文为:\n");
            for(auto c:cipher)
            {
                printf("0x%x ",c);
            }
            printf("\n");
            if(write(nClientSocket,cipher.c_str(),sizeof(cipher))==-1)
            {
                perror("send msg\n");
                exit(0);
            }
            else
            {
                printf("消息已发送\n");
            }
        }
    }
}
void KeyInit(BigInt& des_k)
{
    //swap the rsa key and des key
    extern pair<BigInt,BigInt> pk;//RSA私钥
    extern pair<BigInt,BigInt> sk;//RSA私钥
    if(pk.first.len==0)
    {
        printf("server启动,分配RSA公私钥\n");
        myRSA myrsa;
        myrsa.GenRSAKey();
        pk={myrsa.e,myrsa.n};
        printf("RSA公钥e为:");
        pk.first.display();
        printf("RSA公有钥n为:");
        pk.second.display();
        sk={myrsa.d,myrsa.n};
        printf("RSA私钥d为:");
        sk.first.display();
    }
    int ret1=write(nClientSocket,(char*)&pk,sizeof(pk));
    if(ret1>0)
    {
        BigInt tmp;
        int ret2=read(nClientSocket,(char*)&tmp,sizeof(tmp));
        if(ret2>0)
        {
            printf("recv DES key,begin RSA decrypt...\n");
            //解密des_k
            des_k=Power(tmp,sk.first,sk.second);
            printf("DES KEY:");
            des_k.display();
        }
        else
        {
            perror("recv DES Key error");
            exit(0);
        }
    }
    else
    {
        perror("Send RSA Public Key Error");
        exit(1);
    }
    


}
void Init()
{
    nServSocket=socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in ServAddr, sRemoteAddr;
    ServAddr.sin_family = AF_INET;
    ServAddr.sin_port = htons(7777);
    ServAddr.sin_addr.s_addr = inet_addr("127.0.0.2");
    socklen_t nLength=sizeof(sRemoteAddr);
    if (bind(nServSocket, (struct sockaddr *) &ServAddr, sizeof(struct sockaddr))== -1)
    {
        perror("bind");
        exit(1);
    }
    printf("Socket 初始化完毕,开始监听...\n");
    if (listen(nServSocket, 5) == -1) 
    {
        perror("listen");
        exit(1);
    }
    
    while(true)
    {
        nClientSocket = accept(nServSocket,NULL,NULL);
        printf("server: got connection from %s, port %d,socket %d\n",inet_ntoa(sRemoteAddr.sin_addr),ntohs(sRemoteAddr.sin_port),nClientSocket);
        printf("Key Allocation ...\n");
        BigInt des_k;
        KeyInit(des_k);
        //fork
        pid_t npid;
        npid=fork();
        if(npid<0)
        {
            printf("fork error");
            return;
        }
        else if(npid==0)
        {
            close(nServSocket);
            //child thread
            SecretChat(nClientSocket,inet_ntoa(sRemoteAddr.sin_addr),des_k);

            close(nClientSocket);
            exit(EXIT_SUCCESS);
        }
        else
        {
            //father thread,nothing to do
            close(nClientSocket);
        }
    }
}
