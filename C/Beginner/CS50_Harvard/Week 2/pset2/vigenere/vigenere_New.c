//vigenere
//ά�����Ǽ��ܷ���
	//�ǿ������ܵĸĽ��汾
	//��һ����Կ����Ϊ���ĵ�ƫ��ֵ
	//ʹ�����Ĳ�����ԭ�ľ�����ͬ��Ƶ��, ʹƵ�ʷ����ƽ�ķ���ʧЧ
	//ͬһ����ĸ���Ա����ܳɲ�ͬ����ĸ
	//�������Կ̫����Ȼ�м���ѭ
	//��ͨ����ͬ����ĸ���²���Կ����, ����������������²�ؼ���
	//��õ������, ��Կ�ĳ��Ȳ�С������, ���������޷��ƽ�


//�������

//��ȡ�û��������������
	//�����������
		//���������ж�
		//���������ж�
	//����ĸ, ������, �ޱ��

//����Ԥ����
	//ͳһ��������Ĵ�Сд(�������ݴ�Сд �ж�ת������)
	//���ؼ���ת��Ϊƫ��ֵ, �洢Ϊ����

//������ʼ��
//��ʾ�û���������

//�����㷨
	//���˷���ĸ
	//��Сд����ת��
	//������ܷ����뿭����������
	//������Ĺؼ���ƫ��ֵ����
	//��Ϊ�������ܵ�ƫ��ֵ
	
//�������

//�˳�

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define UPPERCASE_OFFSET 65
#define LOWWERCASE_OFFSET 97

int main(int argc, string argv[])
{
	//�������ʼ��
	string ErrorPrompt = "Usage: ./vigenere Keyword \n";
	//����������� У��
	if (argc != 2)
	{
		printf("%s", ErrorPrompt);
		return 1;
	}
	
	int KeywordLength = strlen(argv[1]);
	int ShiftKey[KeywordLength];
	
	//���������ж�
	for (int i = 0; i < KeywordLength; i++)
	{
		if (!isalpha(argv[1][i]))
		{
			printf("%s", ErrorPrompt);
			return 1;
		}
	}
	
	//���ؼ��� ת��Ϊ ƫ��ֵ����
	for (int i = 0; i < KeywordLength; i++)
	{
		ShiftKey[i] = toupper(argv[1][i]) - UPPERCASE_OFFSET ; 
	}
	
	//������ʼ��
	//��ʾ�û���������
	string PlainText = get_string("plaintext: ");
	int PlainTextLength = strlen(PlainText);
	char CipherText[PlainTextLength];
	int ShiftOffset = 0;
	
	for (int i = 0, j = 0; i < PlainTextLength; i++)
	{
		
		if (isalpha(PlainText[i]) && PlainText[i] != ' ')
		{
			if (j % KeywordLength == 0)
			{
				j = 0;
			}
			ShiftOffset = isupper(PlainText[i]) ? UPPERCASE_OFFSET : LOWWERCASE_OFFSET;
			CipherText[i] = (PlainText[i] - ShiftOffset + ShiftKey[j]) % 26 + ShiftOffset;
			j++;
		}
		else
		{
			CipherText[i] = PlainText[i];	
		}
	}
	
	CipherText[strlen(PlainText)] = '\0';
	//�����㷨
		//���˷���ĸ...checked
		//��Сд����ת��
		//������ܷ����뿭����������
		//������Ĺؼ���ƫ��ֵ����
		//��Ϊ�������ܵ�ƫ��ֵ
		
	//�������
	printf("ciphertext: %s\n", CipherText);
	
}
