//credit
//输入卡号
//仅数字 非字母或符号.
//cs50.h getlong 来实现
#include <cs50.h>
#include <stdio.h>

long get_CreditNumber(string prompt);

int main(void)
{
	//输入卡号
	long CreditNumber = get_CreditNumber("Number: ");
	
	//Luhn’s Algorithm
	int Digit1 = 0;
	int Digit2 = 0;
	int DigitCount = 0;
	int OddSum = 0;
	int EvenSum = 0;
	
	//核心算法
	//逆向偶数位 * 2 各位*数字* 相加
	//逆向奇数位 相加求和
	
	//偶数位 奇数位 之和相加
	
	//并获取卡号前两位数字用于后面的判断逻辑
	
	while (CreditNumber > 0)
	{
		DigitCount++;	//开始计数, 奇数为奇数位, 偶数为偶数位
		Digit1 = Digit2;	//转移
		Digit2 = CreditNumber % 10;	//取余运算获取卡号最后一位数字
		
		if (DigitCount % 2)	//真 时为奇数, 假 为偶数
		{
			OddSum += Digit2;
		}
		else
		{
			int DoubleDigit = Digit2 * 2;
			EvenSum += (DoubleDigit % 10) + (DoubleDigit / 10);
		}
		
		CreditNumber /= 10;	//CreditNumber 整型, 取整数部分进入下一步循环
	}
	
	//debug
    /*
	printf("Digit1: %i\n", Digit1);
	printf("Digit2: %i\n", Digit2);
	printf("OddSum: %i\n", OddSum);
	printf("EvenSum: %i\n", EvenSum);
	printf("DigitCount: %i\n", DigitCount);
	*/
    
	//判断逻辑
	//根据卡号和以及卡号位数
	int FirstTwoDigit = Digit2 * 10 + Digit1;
	bool isValid = (OddSum + EvenSum) % 10 == 0;
	
    if (Digit2 == 4 && DigitCount >= 13 && DigitCount <= 16 && isValid)
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

long get_CreditNumber(string prompt)
{
	long CreditNumber = 0;
	do
	{
		CreditNumber = get_long("%s:", prompt);	
	}
	while (CreditNumber <= 0);
	
	return CreditNumber;
}
