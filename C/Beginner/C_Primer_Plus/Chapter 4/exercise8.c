/*
8����дһ��������ʾ�û����� ���е���� �� ���ĵ������� ��
Ȼ����㲢��ʾ����ÿ����������ʻ��Ӣ������
��ʾС�������һλ���֡�

��������ʹ��1���ش�Լ3.785����1Ӣ���ԼΪ1.609ǧ�ף�
�ѵ�λ��Ӣ��/���ص�ֵת��Ϊ��/100���ŷ��ͨ�õ�ȼ�����ı�ʾ������
����ʾ�������ʾС�������1λ���֡�
ע�⣬�������õķ����������ĵ�λȼ�ϵ��г̣�ֵԽ��Խ�ã���
��ŷ������õ�λ�������ĵ�ȼ�ϲ���������ֵԽ��Խ�ã���
ʹ��#define�������ų�����ʹ��const�޶���������������ʾ����ת��ϵ����


*/

#include <stdio.h>

#define GALLON2LITRE 3.785
#define MILE2KILOMETER 1.609


int main(void)
{
	float gallon, mile;
	printf("input gallon and miles: ");
	
	scanf("%f %f", &gallon, &mile);
	
	
	printf("mile/gallon: %.1f \nLitre/100 km: %.1f", mile / gallon, (gallon * GALLON2LITRE) / (mile * MILE2KILOMETER));
	
	
	return 0;
}
