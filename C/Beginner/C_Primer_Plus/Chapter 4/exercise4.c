/*
4����дһ��������ʾ�û�������ߣ���λ��Ӣ�磩��������

Ȼ��������ĸ�ʽ��ʾ�û����������Ϣ��

Dabney, you are 6.208 feet tall

*/


#include <stdio.h>

int main(void)
{
	float height;
	char name[40];
	
	//prompt input height in inches and name
	printf("Please input height in inches:");
	scanf("%f", &height);
	printf("and your name: ");
	scanf("%s", name);
	
	printf("%s, you are %.3f feet tall", name, height);
	return 0;
}
