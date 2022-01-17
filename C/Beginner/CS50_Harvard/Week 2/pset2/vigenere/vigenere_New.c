//vigenere
//维吉尼亚加密方法
	//是凯撒加密的改进版本
	//以一段秘钥来作为密文的偏移值
	//使得密文不再与原文具有相同的频率, 使频率分析破解的方法失效
	//同一个字母可以被加密成不同的字母
	//但如果秘钥太短仍然有迹可循
	//可通过相同的字母来猜测秘钥长度, 并根据语义分析来猜测关键字
	//最好的情况是, 秘钥的长度不小于明文, 这样基本无法破解


//程序分析

//获取用户命令行输入参数
	//参数错误分析
		//传入数量判断
		//传入内容判断
	//仅字母, 无数字, 无标点

//参数预处理
	//统一输入参数的大小写(或者依据大小写 判断转换方法)
	//将关键字转换为偏移值, 存储为数组

//变量初始化
//提示用户输入明文

//加密算法
	//过滤非字母
	//大小写区分转换
	//具体加密方法与凯撒加密类似
	//将传入的关键字偏移值传入
	//作为凯撒加密的偏移值
	
//输出密文

//退出

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define UPPERCASE_OFFSET 65
#define LOWWERCASE_OFFSET 97

int main(int argc, string argv[])
{
	//错误码初始化
	string ErrorPrompt = "Usage: ./vigenere Keyword \n";
	//传入参数数量 校验
	if (argc != 2)
	{
		printf("%s", ErrorPrompt);
		return 1;
	}
	
	int KeywordLength = strlen(argv[1]);
	int ShiftKey[KeywordLength];
	
	//传入内容判断
	for (int i = 0; i < KeywordLength; i++)
	{
		if (!isalpha(argv[1][i]))
		{
			printf("%s", ErrorPrompt);
			return 1;
		}
	}
	
	//将关键字 转换为 偏移值数字
	for (int i = 0; i < KeywordLength; i++)
	{
		ShiftKey[i] = toupper(argv[1][i]) - UPPERCASE_OFFSET ; 
	}
	
	//变量初始化
	//提示用户输入明文
	string PlainText = get_string("plaintext: ");
	int PlainTextLength = strlen(PlainText);
	char CipherText[PlainTextLength];
	int ShiftOffset = 0;
	
	for (int i = 0, j = 0; i < PlainTextLength; i++)
	{
		
		if (isalpha(PlainText[i]) && PlainText[i] != ' ')
		{
			if (j % KeywordLength == 0)
			{
				j = 0;
			}
			ShiftOffset = isupper(PlainText[i]) ? UPPERCASE_OFFSET : LOWWERCASE_OFFSET;
			CipherText[i] = (PlainText[i] - ShiftOffset + ShiftKey[j]) % 26 + ShiftOffset;
			j++;
		}
		else
		{
			CipherText[i] = PlainText[i];	
		}
	}
	
	CipherText[strlen(PlainText)] = '\0';
	//加密算法
		//过滤非字母...checked
		//大小写区分转换
		//具体加密方法与凯撒加密类似
		//将传入的关键字偏移值传入
		//作为凯撒加密的偏移值
		
	//输出密文
	printf("ciphertext: %s\n", CipherText);
	
}
