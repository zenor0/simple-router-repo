/*
2����дһ�������ȡ���룬����#�ַ�ֹͣ��

����Ҫ��ӡÿ��������ַ��Լ���Ӧ��ASCII�루ʮ���ƣ���
ÿ�д�ӡ8�����ַ�-ASCII�롱��ϡ�

����:ʹ���ַ���������ģ�������%����ÿ8��ѭ������ʱ��ӡһ�����з���
*/

#include <stdio.h>
#define GROUP_COUNT 8

int main(void)
{
	printf("input a sentence. (end by '#')\n");
	char ch;
	long LetterCount = 1;   //ÿ�˸�ѭ������ʮ��ӡһ�����з�
	
	while ((ch = getchar()) != '#')
	{
		if (LetterCount % GROUP_COUNT == 0)
		{
			printf("\n");
		}
		printf("%c - %d\t", ch, ch);
		
		LetterCount++;
	}
	
	printf("\nDone! \n");
	
	return 0;
}
