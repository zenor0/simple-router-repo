/*

6����д�����ȡ���룬����#ֹͣ������ei���ֵĴ�����

*/
#include <stdio.h>

int main(void)
{
	printf("input: ");
	char ch;
	long count = 0;
	
	while ((ch = getchar()) != '#')
	{
        
		if (ch == 'e')
		{

			if ((ch = getchar()) != '#' && ch == 'i')
			{
				count++;
			}
			else if (ch == '#')
		   	{
		  	 	break;
		   	}
		}
        
        /*
        if (ch == 'e')
        {
			ch = getchar();
			switch (ch)
			{
				case 'i' :
					count++;
					break;
				case '#':
					break;
				default:
					continue;
					break;
			}
			break;
        }*/
	}
	
	
	
	printf("count: %d", count);
	
	return 0;
}
