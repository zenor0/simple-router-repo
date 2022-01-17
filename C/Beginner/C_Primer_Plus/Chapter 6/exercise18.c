/*
18．Rabnud博士加入了一个社交圈。起初他有5个朋友。
他注意到他的朋友数量以下面的方式增长。


第1周少了1个朋友，剩下的朋友数量翻倍；
第2周少了2个朋友，剩下的朋友数量翻倍。

一般而言，第N周少了N个朋友，剩下的朋友数量翻倍。


编写一个程序，计算并显示Rabnud博士每周的朋友数量。
该程序一直运行，直到超过邓巴数（Dunbar's number ）。
邓巴数是粗略估算一个人在社交圈中有稳定关系的成员的最大值，该值大约是150。

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
