/*
7．编写一个程序，将一个double类型的变量设置为1.0/3.0，
一个float类型的变量设置为1.0/3.0。
分别显示两次计算的结果各3次：
一次显示小数点后面6位数字；
一次显示小数点后面12位数字；
一次显示小数点后面16位数字。

程序中要包含float.h头文件，并显示FLT_DIG和DBL_DIG的值。
1.0/3.0的值与这些值一致吗？

*/

#include <stdio.h>
#include <float.h>
#include <limits.h>


int main(void)
{
	double i = 1.0 / 3.0;
	float j = 1.0 / 3.0;
	
	printf("i: %.6f\n", i);
	printf("i: %.12f\n", i);
	printf("i: %.16f\n", i);
	
	printf("j: %.6f\n", j);
	printf("j: %.12f\n", j);
	printf("j: %.16f\n", j);
	
	printf("FLT_DIG: %i\nDBL_DIG: %i", FLT_DIG, DBL_DIG);
	return 0;
}
