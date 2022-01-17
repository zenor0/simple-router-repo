//credit
//���뿨��
//������ ����ĸ�����.
//cs50.h getlong ��ʵ��
#include <cs50.h>
#include <stdio.h>

long get_CreditNumber(string prompt);

int main(void)
{
	//���뿨��
	long CreditNumber = get_CreditNumber("Number: ");
	
	//Luhn��s Algorithm
	int Digit1 = 0;
	int Digit2 = 0;
	int DigitCount = 0;
	int OddSum = 0;
	int EvenSum = 0;
	
	//�����㷨
	//����ż��λ * 2 ��λ*����* ���
	//��������λ ������
	
	//ż��λ ����λ ֮�����
	
	//����ȡ����ǰ��λ�������ں�����ж��߼�
	
	while (CreditNumber > 0)
	{
		DigitCount++;	//��ʼ����, ����Ϊ����λ, ż��Ϊż��λ
		Digit1 = Digit2;	//ת��
		Digit2 = CreditNumber % 10;	//ȡ�������ȡ�������һλ����
		
		if (DigitCount % 2)	//�� ʱΪ����, �� Ϊż��
		{
			OddSum += Digit2;
		}
		else
		{
			int DoubleDigit = Digit2 * 2;
			EvenSum += (DoubleDigit % 10) + (DoubleDigit / 10);
		}
		
		CreditNumber /= 10;	//CreditNumber ����, ȡ�������ֽ�����һ��ѭ��
	}
	
	//debug
    /*
	printf("Digit1: %i\n", Digit1);
	printf("Digit2: %i\n", Digit2);
	printf("OddSum: %i\n", OddSum);
	printf("EvenSum: %i\n", EvenSum);
	printf("DigitCount: %i\n", DigitCount);
	*/
    
	//�ж��߼�
	//���ݿ��ź��Լ�����λ��
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
