//caesar
//�����������

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define UPPERCASE_OFFSET 65
#define LOWWERCASE_OFFSET 97

int main(int argc, string argv[])
{

	//��������Ĵ���
	//Usage: caesar Shiftkey
	//int main(int argc, string argv[])
	//ע�� return �������ʹ��

	string errorPrompt = "Usage: ./caesar Shiftkey\n";	//������
	//�����������
	if (argc != 2)
	{
		printf("%s", errorPrompt);
		return 1;
	}

	//�Ƿ����ִ����� ,����������� ��atoi()�������м��
	for (int i = 0, j = strlen(argv[1]); i < j; i++)
	{
		if (i == 0 && argv[1][i] == '-')
		{
			continue;
		}
		else if (!isdigit(argv[1][i]))
		{
			printf("%s", errorPrompt);
			return 1;
		}
	}

	//string ��int
	int ShiftKey = 0;
	//���ֵ�Ԥ����
		//������ת��
		//����26���ֵ�ת��

	if (atoi(argv[1]) < 0)	//����������ֵת��Ϊ ��Ч����ƫ��ֵ
	{
		ShiftKey = 26 - ((atoi(argv[1]) * -1) % 26);
	}
	else if (atoi(argv[1]) > 0)
	{
		ShiftKey = atoi(argv[1]) % 26;
	}
		//���յõ�ƫ��ֵ shiftkey

	//��ʾ�û�����ԭ��
	string PlainText = get_string("plaintext: ");
	char CipherText[strlen(PlainText)];	//��ʼ����������
	int ShiftOffset = 0;

	//for ѭ�����������ַ�
	for (int i = 0, j = strlen(PlainText); i < j; i++)
	{

		//����ĸ�Ĺ���
		if (isalpha(PlainText[i]))
		{
			//��Сд��ĸ������
			ShiftOffset = isupper(PlainText[i]) ? UPPERCASE_OFFSET : LOWWERCASE_OFFSET;
			//�����㷨
				//ASCII���ת�� �� 0-26 (% �ؼ�)
				//Ӧ��ƫ��ֵ
					//% ȡ�������ʹ��
				//��ת��ΪASCII��
			CipherText[i] = (PlainText[i] - ShiftOffset + ShiftKey) % 26 + ShiftOffset;
		}
		else
		{
			CipherText[i] = PlainText[i];
		}
	}
	CipherText[strlen(PlainText) + 1] = '\0';
	

	//����������Ϊ�ַ������??
	printf("ciphertext: %s\n", CipherText);
	//�����ַ����??

}
