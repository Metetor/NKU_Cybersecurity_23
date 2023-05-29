#include<iostream>
#include<cstring>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include"conf.h"
#include"myDES.h"
#include"chat.h"
#include"tool.h"
using std::cin;
bitset<64> key;
extern char sendBuf[BUFFERSIZE];
extern char recvBuf[BUFFERSIZE];
void SecretChat(int nSock,char *pRemoteName)
{
    extern BigInt des_k;
    for(int i=0;i<2;i++)
    {
        for(int j=0;j<32;j++)
        {
            key[i * 2 + j] = (des_k.data[i] >> (31 - j)) & 1;
        }
    }
    DES cDes;
    pid_t nPid;
    nPid=fork();
    if(nPid<0)
    {
        printf("fork fault");
        return;
    }
    else if(nPid==0)
    {
        //recv thread
        extern char recvBuf[BUFFERSIZE];
        while(1)
        { 
            bzero(recvBuf,BUFFERSIZE);
            read(nSock,recvBuf,BUFFERSIZE);
            string cipher=recvBuf;
            if(cipher=="")
                break;
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
void KeyInit()
{
    extern pair<BigInt,BigInt> pk;
    //recv the public key
    int ret1=read(nClientSocket,(char*)&pk,sizeof(pk));
    if(ret1>0)
    {
        printf("recv RSA public key from server\n");
        //generate DES key
        extern BigInt des_k;
        printf("generate DES key,please input random seed\n");
        int seed;
        cin>>seed;
        des_k.Random(2,seed);
        BigInt enc_des_k;
        des_k.display();
        enc_des_k=Power(des_k,pk.first,pk.second);
        int ret2=write(nClientSocket,(char*)&enc_des_k,sizeof(enc_des_k));
        if(ret2>0)
        {
            printf("send des_k success\n");
            return;
        }
        else
        {
            perror("send des_k error");
            exit(0);
        }
    }
    else
    {
        perror("recv RSA Public Key Error");
        exit(0);
    }
}
void Init()
{
    
    char strIpAddr[16];
    printf("请输入服务器IP: ");
    cin>>strIpAddr;
    int nLength;
    struct sockaddr_in ServAddr;
    if ((nClientSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    {
        perror("Socket");
        exit(errno);
    }
    ServAddr.sin_family = AF_INET;
    ServAddr.sin_port = htons(7777);
    ServAddr.sin_addr.s_addr = inet_addr(strIpAddr);
    printf("Socket 初始化完成，开始连接...\n");
    if (connect(nClientSocket, (struct sockaddr *) &ServAddr, sizeof(ServAddr)) != 0) 
    {
        perror("Connect ");
        exit(errno);
    }
    else
    {
        printf("Connect to Server! \nThen allocate the keys...\n");
        KeyInit();
        SecretChat(nClientSocket,strIpAddr); 
    }
    close(nClientSocket);
}