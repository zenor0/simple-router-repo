/*
3����дһ�����򣬶�ȡһ����������������С�����������ӡ��
Ȼ����ָ����������ӡ��������ĸ�ʽ�������
��ϵͳ��ͬ��ָ����������ʾ��λ�����ܲ�ͬ����

����a��The input is21.3 or2.1e+001.

����b��The input is+21.290 or2.129E+001.
*/

#include <stdio.h>

int main(void)
{
	float num;
	
	printf("input a float: ");
	scanf("%f", &num);
	
	printf("The input is %.1f or %.1e\n", num, num);
	printf("The input is %+.3f or %.3e\n", num, num);
	
	return 0;
}
