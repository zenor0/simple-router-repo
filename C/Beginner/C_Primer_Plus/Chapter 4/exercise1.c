#include <stdio.h>
//1����дһ��������ʾ�û����������գ�Ȼ���ԡ���,�ա��ĸ�ʽ��ӡ������
int main(void)
{
	char firstname[40];
	char lastname[40];
	
    printf("input first name and last name: ");
    scanf("%s %s", firstname, lastname);
    printf("%s %s", lastname, firstname);
    
    
    return 0;
}
