//substitution
//单表替换密码

//程序分析
//启动

// 传入密码表
    // 检测传入参数数量
    // 检测传入第一个参数的长度
    // 是否均为字母

    //转换为偏移值 ShiftKey 数组

// 提示用户输入 原文


// 加密逻辑

    // 跳过 非字母
    // ASCII码 转换
    // 对应密码表输出相应密文

// 输出密文

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define UPPERCASE_OFFSET 65
#define LOWWERCASE_OFFSET 97

int main(int argc, string argv[])
{
    // 检测传入参数数量
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // 初始化 ShiftKey 数组
    int ShiftKey[26];

    // 检测传入参数内容
    if (strlen(argv[1]) == 26)  // 检测输入字符量
    {
        for (int i = 0; i < 26; i++)
        {
            if (isalpha(argv[1][i]) == 0)   // 检测是否字母
            {
                printf("Key must contain 26 characters.\n");
                return 1;
            }
            ShiftKey[i] = toupper(argv[1][i]) - UPPERCASE_OFFSET;   // 小写字母转大写, 并得到 Shiftkey 数组
        }

        // 检测是否有重复字母
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



    //提示用户输入原文
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

    //输出密文

    printf("ciphertext: %s\n", CipherText);
    return 0;

}
