//credit
//输入卡号
//仅数字 非字母或符号.
//用字符串, 数组功能来实现
//char 和 int 的转换出问题了...未解决Unchecked

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	//输入卡号
	bool notFormatted = 0;
	int DigitCount = 0;
	string CreditNumber = 0;
	
	do
	{
	CreditNumber = get_string("Number: ");
	DigitCount = strlen(CreditNumber);
	for (int i = 0; i < DigitCount; i++)
	{
		if (!(CreditNumber[i] >= '0' && CreditNumber[i] <= '9'))
		{
			notFormatted = 1;
			break;
		}
	}
	}while(notFormatted);
	
	//Luhn’s Algorithm
	int FirstTwoDigit = atoi(&CreditNumber[0]) * 10 + atoi(&CreditNumber[1]);
	int OddSum = 0;
	int EvenSum = 0;
	//核心算法
	//逆向偶数位 * 2 各位*数字* 相加
	//逆向奇数位 相加求和
	
	//偶数位 奇数位 之和相加
	
	//并获取卡号前两位数字用于后面的判断逻辑
	int tempDigit = 0;
	int tempDouble = 0;
	for (int i = 0; i > DigitCount; i++)
	{
		tempDigit = atoi(&CreditNumber[DigitCount - i]);
		if (i % 2)	//假为奇数, 真为偶数
		{
			tempDouble = tempDigit * 2;
			EvenSum += (tempDigit % 10) + (tempDigit / 10);
		}
		else
		{
			OddSum += tempDigit;
		}
	}
	
	//debug
	printf("FirstTwoDigit: %i\n", FirstTwoDigit);
	printf("OddSum: %i\n", OddSum);
	printf("EvenSum: %i\n", EvenSum);
	printf("DigitCount: %i\n", DigitCount);
    
	//判断逻辑
	//根据卡号和以及卡号位数
	
	bool isValid = (OddSum + EvenSum) % 10 == 0;
	
    if (atoi(CreditNumber[0]) == 4 && DigitCount >= 13 && DigitCount <= 16 && isValid)
    {
        printf("VISA\n");
    }
    else if (FirstTwoDigit >= 51 && FirstTwoDigit <= 55 && DigitCount == 16 && isValid)
    {
        printf("MASTERCARD\n");
    }
    else if ((FirstTwoDigit == 34 || FirstTwoDigit == 37) && DigitCount == 15 && isValid)
    {
        printf("AMEX\n");
    }
    else
    {
        printf("INVALID\n");
    }
}
