/*
1����дһ�����򣬰��÷��ӱ�ʾ��ʱ��ת������Сʱ�ͷ��ӱ�ʾ��ʱ�䡣
ʹ��#define ��const ����һ����ʾ60 �ķ��ų�����const ������
ͨ��while ѭ�����û��ظ�����ֵ��
ֱ���û�����С�ڻ����0 ��ֵ��ֹͣѭ����
*/

#include <stdio.h>

#define TIME 60

int main(void)
{
	int minutes;
	printf("input time in minute: ");
	scanf("%d", &minutes);

	while (minutes > 0)
	{
		printf("%d hours, %d minutes\n", minutes / TIME, minutes % TIME);
		printf("next?(input a num smaller or equal to 0 to exit)");
		scanf("%d", &minutes);
	}
	printf("bye")
	
	return 0;
}
