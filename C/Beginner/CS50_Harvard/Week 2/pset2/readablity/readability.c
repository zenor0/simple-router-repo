//caesar
//凯撒密码加密

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define UPPERCASE_OFFSET 65
#define LOWWERCASE_OFFSET 97

int main(int argc, string argv[])
{

	//传入参数的处理
	//Usage: caesar Shiftkey
	//int main(int argc, string argv[])
	//注意 return 错误码的使用

	string errorPrompt = "Usage: ./caesar Shiftkey\n";	//错误码
	//参数数量检测
	if (argc != 2)
	{
		printf("%s", errorPrompt);
		return 1;
	}

	//是否数字传入检测 ,遍历输入参数 用atoi()函数进行检测
	for (int i = 0, j = strlen(argv[1]); i < j; i++)
	{
		if (i == 0 && argv[1][i] == '-')
		{
			continue;
		}
		else if (!isdigit(argv[1][i]))
		{
			printf("%s", errorPrompt);
			return 1;
		}
	}

	//string →int
	int ShiftKey = 0;
	//数字的预处理
		//负数的转换
		//超出26数字的转换

	if (atoi(argv[1]) < 0)	//将负数输入值转换为 等效的正偏移值
	{
		ShiftKey = 26 - ((atoi(argv[1]) * -1) % 26);
	}
	else if (atoi(argv[1]) > 0)
	{
		ShiftKey = atoi(argv[1]) % 26;
	}
		//最终得到偏移值 shiftkey

	//提示用户输入原文
	string PlainText = get_string("plaintext: ");
	char CipherText[strlen(PlainText)];	//初始化密文数组
	int ShiftOffset = 0;

	//for 循环遍历所有字符
	for (int i = 0, j = strlen(PlainText); i < j; i++)
	{

		//非字母的过滤
		if (isalpha(PlainText[i]))
		{
			//大小写字母的区分
			ShiftOffset = isupper(PlainText[i]) ? UPPERCASE_OFFSET : LOWWERCASE_OFFSET;
			//加密算法
				//ASCII码的转换 → 0-26 (% 关键)
				//应用偏移值
					//% 取余运算的使用
				//逆转换为ASCII码
			CipherText[i] = (PlainText[i] - ShiftOffset + ShiftKey) % 26 + ShiftOffset;
		}
		else
		{
			CipherText[i] = PlainText[i];
		}
	}
	CipherText[strlen(PlainText) + 1] = '\0';
	

	//存入数组作为字符串输出??
	printf("ciphertext: %s\n", CipherText);
	//单个字符输出??

}
