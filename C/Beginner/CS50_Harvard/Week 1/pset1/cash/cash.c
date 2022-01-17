#include <cs50.h>
#include <stdio.h>
#include <math.h>


float get_dollar(string prompt);

int main(void)
{
	//��������
	//ʹ��round()����ȡ��
	int cent = round(100 * get_dollar("Change owed: "));
	
	//�����߼�
	//ʹ��ȡ������ % ʵ��
	int bill[] = {25, 10, 5, 1};
	int AmountsCount = sizeof(bill) / sizeof(int);	//�������� bill �е�Ԫ�ظ���, ʵ��Ԫ�ظ����Ķ�̬����
	int bill_count[AmountsCount];
	
	for (int i = 0, centDecoy = cent; i < AmountsCount; i++)
	{
		bill_count[i] = centDecoy / bill[i];	//int ����, ������Զ�ȡ��������
		centDecoy %= bill[i];
	}
	
	//������
	printf("Here is the result: \nYou will have\n");
	for (int i = 0; i < AmountsCount; i++)
	{
		printf("%i cent: %i\n", bill[i], bill_count[i]);
	}

}

float get_dollar(string prompt)
{
	float dollar;
	do
	{
		dollar = get_float("%s",prompt);
	}
	while (!(dollar > 0));
	
	return dollar;
}
