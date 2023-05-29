#ifndef TOOL_H
#define TOOL_H
#include<bitset>
using namespace std;
bitset<64> stob(char s[8]);
bitset<64> stob(string s8);
string btos(bitset<64> bits);
void bitsetTohex(bitset<64> binset);

#endif // !TOOL_H

