//substitution
//�����滻����

//�������
//����

// ���������
    // ��⴫���������
    // ��⴫���һ�������ĳ���
    // �Ƿ��Ϊ��ĸ

    //ת��Ϊƫ��ֵ ShiftKey ����

// ��ʾ�û����� ԭ��


// �����߼�

    // ���� ����ĸ
    // ASCII�� ת��
    // ��Ӧ����������Ӧ����

// �������

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define UPPERCASE_OFFSET 65
#define LOWWERCASE_OFFSET 97

int main(int argc, string argv[])
{
    // ��⴫���������
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // ��ʼ�� ShiftKey ����
    int ShiftKey[26];

    // ��⴫���������
    if (strlen(argv[1]) == 26)  // ��������ַ���
    {
        for (int i = 0; i < 26; i++)
        {
            if (isalpha(argv[1][i]) == 0)   // ����Ƿ���ĸ
            {
                printf("Key must contain 26 characters.\n");
                return 1;
            }
            ShiftKey[i] = toupper(argv[1][i]) - UPPERCASE_OFFSET;   // Сд��ĸת��д, ���õ� Shiftkey ����
        }

        // ����Ƿ����ظ���ĸ
        for (int i = 0; i < 26; i++)
        {
            for (int j = 0; j < 26; j++)
            {
                if (ShiftKey[i] == ShiftKey[j] && i != j)
                {
                    printf("Same exist!\n");
                    return 1;
                }
            }
        }
    }
    else
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }



    //��ʾ�û�����ԭ��
    string PlainText = get_string("plaintext: ");
    int StringLength = strlen(PlainText);
    char CipherText[StringLength];
    int tempOffset = 0;

    for (int i = 0; i < StringLength; i++)
    {
        if (isalpha(PlainText[i]))
        {
            tempOffset = isupper(PlainText[i]) ? UPPERCASE_OFFSET : LOWWERCASE_OFFSET;
            CipherText[i] = ShiftKey[PlainText[i] - tempOffset] + tempOffset;
        }
        else
        {
            CipherText[i] = PlainText[i];
        }
    }

    CipherText[StringLength] = '\0';

    //�������

    printf("ciphertext: %s\n", CipherText);
    return 0;

}
