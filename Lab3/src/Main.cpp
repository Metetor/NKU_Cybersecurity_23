#include"md5.h"
#include"helperFunc.h"
#include<unordered_map>

//Linux 字节序的问题，看看明天能不能解决一下，解决不了就写Windows上面报告。。。

//解决方法:Linux上面的unsigned long 是8个byte,定义DWORD时改变为unsigned int就行了

int main(int argc,char *argv[])
{
    std::unordered_map<std::string, void(*)(int, char*[])> mapOp = {
    {"-t", print_t}, 
    {"-h", print_h}, 
    {"-c", print_c}, 
    {"-v", print_v}, 
    {"-f", print_f}
    };
    if(argc<2)
    {
        printf("参数错误,argc=%d",argc);
        return -1;
    }
    std::string opcode=argv[1];
    if(mapOp.find(opcode)!=mapOp.end())
    {
        mapOp[opcode](argc,argv);
    }
    return 0;
}