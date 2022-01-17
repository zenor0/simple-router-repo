#include <stdio.h>
//1．编写一个程序，提示用户输入名和姓，然后以“名,姓”的格式打印出来。
int main(void)
{
	char firstname[40];
	char lastname[40];
	
    printf("input first name and last name: ");
    scanf("%s %s", firstname, lastname);
    printf("%s %s", lastname, firstname);
    
    
    return 0;
}
