/*
2����дһ��������ʾ�û��������֣���ִ�����²�����

����a����ӡ���֣�����˫���ţ�

����b���ڿ��Ϊ20 ���ֶ��Ҷ˴�ӡ���֣�����˫���ţ�

����c���ڿ��Ϊ20 ���ֶ���˴�ӡ���֣�����˫���ţ�

����d���ڱ�������ȿ�3 ���ֶ��д�ӡ���֡�
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
