/*
7����дһ�����򣬽�һ��double���͵ı�������Ϊ1.0/3.0��
һ��float���͵ı�������Ϊ1.0/3.0��
�ֱ���ʾ���μ���Ľ����3�Σ�
һ����ʾС�������6λ���֣�
һ����ʾС�������12λ���֣�
һ����ʾС�������16λ���֡�

������Ҫ����float.hͷ�ļ�������ʾFLT_DIG��DBL_DIG��ֵ��
1.0/3.0��ֵ����Щֵһ����

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
