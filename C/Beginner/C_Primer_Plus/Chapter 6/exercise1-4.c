/*
1����дһ�����򣬴���һ������26��Ԫ�ص����飬�������д���26��Сд��ĸ��Ȼ���ӡ������������ݡ�

2��ʹ��Ƕ��ѭ����������ĸ�ʽ��ӡ�ַ���

$
$$
$$$
$$$$
$$$$$




3��ʹ��Ƕ��ѭ����������ĸ�ʽ��ӡ��ĸ��

F
FE
FED
FEDC
FEDCB
FEDCBA

Ȼ���������±�ѡ�񵥶�����ĸ������lets[0] ��'A' ���ȵȡ�

4��ʹ��Ƕ��ѭ����������ĸ�ʽ��ӡ��ĸ��
A
BC
DEF
GHIJ
KLMNO
PQRSTU

������ϵͳ��ʹ��������˳�����Ĵ��룬�������ϰ3�ķ��������
*/

#include <stdio.h>
int exercise1(void);
int exercise2(void);
int exercise3(void);
int exercise4(void);

int main(void)
{
	return exercise4();
}

int exercise1(void)
{
	//��дһ�����򣬴���һ������26��Ԫ�ص����飬�������д���26��Сд��ĸ��Ȼ���ӡ������������ݡ�
	const int size = 26;
	char alphabet[size];
	alphabet[0] = 'a';
	
	for (int i = 0; i < size; i++)
	{
		alphabet[i] = 'a' + i;
	}
	
	for (int i = 0; i < size; i++)
	{
		printf("%c", alphabet[i]);
	}
	
	return 0;
}

int exercise2(void)
{
	const int row = 5;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j <= i ; j++)
		{
			printf("$");
		}
		printf("\n");
	}
	
	return 0;
}

int exercise3(void)
{
	const int row = 6;
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j <= i ; j++)
		{
			printf("%c", 'F' - j);
		}
		printf("\n");
	}

	return 0;
}

int exercise4(void)
{
	const int row = 6;
	for (int i = 0, count = 0; i < row; i++)
	{
		for (int j = 0; j <= i ; count++, j++)
		{
			printf("%c", 'A' + count);
		}
		printf("\n");
	}

	return 0;
}

