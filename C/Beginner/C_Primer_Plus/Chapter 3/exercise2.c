/*
2．编写一个程序，要求提示输入一个ASCII码值（如，66），然后打印输入的字符。
*/

#include <stdio.h>

int main(void)
{
	int asciiCode;
	printf("num2ascii\ninput a number: ");
	scanf("%i", &asciiCode);
	
	printf("%c", asciiCode);
	return 0;
}
