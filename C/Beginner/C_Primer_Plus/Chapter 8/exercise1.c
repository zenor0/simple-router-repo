/*1����дһ�������ȡ���룬����#�ַ�ֹͣ��Ȼ�󱨸��ȡ�Ŀո��������з��������������ַ���������
*/

#include <stdio.h>

int main(void)
{
	
	printf("input a sentence:");
	
	char ch;
	
	long SpaceCount, LineCount, OthersCount;
	SpaceCount = OthersCount = 0;
	LineCount = 1;  // ���һ��, �����ܴ��� 1
	
	
	while ((ch = getchar()) != '#') // �ڻ�ȡ�� '#' ֮ǰ, ѭ��
	{
		switch (ch)
		{
			case ' ':
				SpaceCount++;  // �ո�
				break;
			case '\n':
				LineCount++;
				break;
			default:
				OthersCount++;
				break;
		}
	}
	
	printf("Done!\n");
	printf("In this paragraph: %ld spaces, %ld lines, %ld other letters.\n", SpaceCount, LineCount, OthersCount);
	
	return 0;
}
