/*
6����дһ����������ʾ�û���������Ȼ����ʾ�û������ա�
��һ�д�ӡ�û�����������գ���һ�зֱ��ӡ�����յ���ĸ����
��ĸ��Ҫ����Ӧ�����յĽ�β���룬������ʾ��

Melissa Honeybee
      7        8




���������ٴ�ӡ��ͬ����Ϣ��������ĸ��������Ӧ�����յĿ�ͷ���룬������ʾ��

Melissa Honeybee
7       8

*/

#include <stdio.h>
#include <string.h>

int main(void)
{
	char firstname[40];
	char lastname[40];
	
	printf("firstname and lastname: ");
	scanf("%s %s", firstname, lastname);
	
	printf("%s %s\n", firstname, lastname);
	printf("%*d %*d\n", strlen(firstname), strlen(firstname), strlen(lastname), strlen(lastname));

	printf("%s %s\n", firstname, lastname);
	printf("%-*d %-*d", strlen(firstname), strlen(firstname), strlen(lastname), strlen(lastname));
	return 0;
}
