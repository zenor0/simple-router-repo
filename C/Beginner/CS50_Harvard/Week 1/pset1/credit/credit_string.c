//credit
//���뿨��
//������ ����ĸ�����.
//���ַ���, ���鹦����ʵ��
//char �� int ��ת����������...δ���Unchecked

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	//���뿨��
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
	
	//Luhn��s Algorithm
	int FirstTwoDigit = atoi(&CreditNumber[0]) * 10 + atoi(&CreditNumber[1]);
	int OddSum = 0;
	int EvenSum = 0;
	//�����㷨
	//����ż��λ * 2 ��λ*����* ���
	//��������λ ������
	
	//ż��λ ����λ ֮�����
	
	//����ȡ����ǰ��λ�������ں�����ж��߼�
	int tempDigit = 0;
	int tempDouble = 0;
	for (int i = 0; i > DigitCount; i++)
	{
		tempDigit = atoi(&CreditNumber[DigitCount - i]);
		if (i % 2)	//��Ϊ����, ��Ϊż��
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
    
	//�ж��߼�
	//���ݿ��ź��Լ�����λ��
	
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
