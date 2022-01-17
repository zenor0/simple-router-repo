/*
4．编写一个程序，提示用户输入身高（单位：英寸）和姓名，

然后以下面的格式显示用户刚输入的信息：

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
