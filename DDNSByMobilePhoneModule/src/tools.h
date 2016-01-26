#ifndef __TOOLS_H__
#define __TOOLS_H__

extern char HexTable[]; //ascii－>hex的转换表
extern char HEXStr[32];	//数据转换临时内存
extern char sssStr[5];		//数据转换临时内存
extern char caNewString[1024];	 //注意定义在函数内部容易堆栈溢出 此值的范围不能小于最后一次查询的内存位置

void Hex2HexStr(unsigned char hex);
void Hex2Str(unsigned char hex);
void U16_2Str(unsigned int portnum);
int ReplaceStr(char *sSrc, char *sSubStr, char *sReplaceStr);
static char *itoa(int value, char *string, int radix);
void Get_SerialNum(void);

#endif
