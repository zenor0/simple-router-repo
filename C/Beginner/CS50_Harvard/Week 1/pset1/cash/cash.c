#include <cs50.h>
#include <stdio.h>
#include <math.h>


float get_dollar(string prompt);

int main(void)
{
	//输入数字
	//使用round()函数取整
	int cent = round(100 * get_dollar("Change owed: "));
	
	//处理逻辑
	//使用取余运算 % 实现
	int bill[] = {25, 10, 5, 1};
	int AmountsCount = sizeof(bill) / sizeof(int);	//计算数组 bill 中的元素个数, 实现元素个数的动态调整
	int bill_count[AmountsCount];
	
	for (int i = 0, centDecoy = cent; i < AmountsCount; i++)
	{
		bill_count[i] = centDecoy / bill[i];	//int 类型, 相除后自动取整数部分
		centDecoy %= bill[i];
	}
	
	//结果输出
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
