/*
2．编写一个程序，提示用户输入名字，并执行以下操作：

　　a．打印名字，包括双引号；

　　b．在宽度为20 的字段右端打印名字，包括双引号；

　　c．在宽度为20 的字段左端打印名字，包括双引号；

　　d．在比姓名宽度宽3 的字段中打印名字。
*/

#include <stdio.h>
#include <string.h>


int main(void)
{
	char name[40];
	
    printf("input a name: ");
	scanf("%s", name);
	
	printf("\"%s\"\n", name);
	
	printf("\"%20s\"\n", name);
	printf("\"%-20s\"\n", name);
	printf("%*s\n", printf("\"%-20s\"\n", name) + 3, name);
	
    return 0;
}
