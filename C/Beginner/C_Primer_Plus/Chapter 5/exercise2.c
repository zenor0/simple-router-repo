/*
2����дһ��������ʾ�û�����һ��������
Ȼ���ӡ�Ӹ������ȸ�����10 ����������
�����磬�û�����5 �����ӡ5 ��15 ����������������5 ��15 ����
Ҫ���ӡ�ĸ�ֵ֮����һ���ո��Ʊ�����з��ֿ���
*/

#include <stdio.h>

int main(void)
{
	int num;
	printf("input a num: ");
	scanf("%d", &num);
	int threshold = num + 10;
	
	
	
	while (num <= threshold)
	{
		printf("%d\n", num);
		num++;
	}
	
	return 0;
}
