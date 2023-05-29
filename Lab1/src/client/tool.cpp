#include"tool.h"
bitset<64> stob(char s[8])
{
	bitset<64> bits;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			bits[i * 8 + j] = (s[i] >> (7 - j)) & 1;
		}
	}
	return bits;
}
bitset<64> stob(string s8)
{
	bitset<64> bits;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			bits[i * 8 + j] = (s8[i] >> (7 - j)) & 1;
		}
	}
	return bits;
}
string btos(bitset<64> bits) {
	string res;
	uint8_t sum;
	for (int i = 0; i < 8; i++)
	{
		sum = 0;
		for (int j = 7; j >= 0; j--)
		{
			sum += bits[i * 8 + j] * pow(2, 7 - j);
		}
		res += (char)sum;
		//printf("0x%X ", sum);
	}
	return res;
};
void bitsetTohex(bitset<64> binset) {
	uint8_t sum;
	for (int i = 0; i < 8; i++)
	{
		sum = 0;
		for (int j = 7; j >= 0; j--)
		{
			sum += binset[i * 8 + j] * pow(2, 7 - j);
		}
		printf("0x%X ", sum);
	}
	return;
}