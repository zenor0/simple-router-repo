/*
5����дһ��������ʾ�û���������λÿ�루Mb/s��Ϊ��λ�������ٶ�
�������ֽڣ�MB��Ϊ��λ���ļ���С��
������Ӧ�����ļ�������ʱ�䡣
ע�⣬����1�ֽڵ���8λ��
ʹ��float���ͣ�����/��Ϊ���š�
�ó���Ҫ������ĸ�ʽ��ӡ3��������ֵ�������ٶȡ��ļ���С������ʱ�䣩��
��ʾС���������λ���֣�

At 18.12 megabits per second, a file of 2.20 megabytes
downloads in 0.97 seconds.


*/

#include <stdio.h>

int main(void)
{
	float downloadspeed, filesize;
	
	printf("downloadspeed(Mb/s) and file size(MB):");
	scanf("%f %f", &downloadspeed, &filesize);
	
	float time = (filesize * 8) / downloadspeed;
	printf("At %.2f megabits per second, a file of %.2f megabytes\n"
			"downloads in %.2f seconds.", downloadspeed, filesize, time);
			
	return 0;
}
