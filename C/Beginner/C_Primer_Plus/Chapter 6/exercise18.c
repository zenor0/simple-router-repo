/*
18��Rabnud��ʿ������һ���罻Ȧ���������5�����ѡ�
��ע�⵽������������������ķ�ʽ������


��1������1�����ѣ�ʣ�µ���������������
��2������2�����ѣ�ʣ�µ���������������

һ����ԣ���N������N�����ѣ�ʣ�µ���������������


��дһ�����򣬼��㲢��ʾRabnud��ʿÿ�ܵ�����������
�ó���һֱ���У�ֱ�������˰�����Dunbar's number ����
�˰����Ǵ��Թ���һ�������罻Ȧ�����ȶ���ϵ�ĳ�Ա�����ֵ����ֵ��Լ��150��

*/

#include <stdio.h>

int main(void)
{

	int FriendsCount = 5;
	int WeekCount = 1;
	
	while(FriendsCount < 150)
	{
		printf("This is Week %d. \n", WeekCount);
		
		FriendsCount -= WeekCount;
		FriendsCount *= 2;
		
		printf("Dr. Rabnud has %d friends.\n\n\n", FriendsCount);
		WeekCount++;
	}


	printf("DONE! STABLE!!\n");
	
	return 0;
}
