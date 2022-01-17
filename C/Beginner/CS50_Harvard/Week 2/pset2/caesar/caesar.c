#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#define LETTER_COUNTS 26
#define UPPERCASE_LETTERS_START 65
#define LOWERCASE_LETTERS_START 97

int main(int argc, string argv[])
{
	//check argument count
	if (argc != 2)
	{
		printf("Usage: ./caesar key\n");
		return 1;
	}
		
    //argv[1] check function
    int arglength = strlen(argv[1]);
    for (int i = 0; i < arglength; i++)	//check if number
    {
        if(i == 0 && argv[1][i] == '-')
        {
            continue;
        }
        else if (! isdigit(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    
    //argument pre-process    
    int shift;
    if (atoi(argv[1]) < 0)		//when negative , make it as positive
    {
		shift = - (-1 * atoi(argv[1]) ) % LETTER_COUNTS + LETTER_COUNTS;
	}
	else	//when positive and zero
	{
		shift = atoi(argv[1]) % LETTER_COUNTS; // make sure it will not be beyond 26;
	}
	
	//printf("shift number:%i\n", shift); 
	string plaintext = get_string("plaintext:");
    int strlength = strlen(plaintext);
	char ciphertext[strlength];
    int temptext;
	int asciioffset;
	
	
    printf("ciphertext:");

	for (int i = 0; i < strlength ; i++)
	{
		if(isalpha(plaintext[i]))
		{
			asciioffset = isupper(plaintext[i]) ? UPPERCASE_LETTERS_START : LOWERCASE_LETTERS_START;
			temptext = (plaintext[i] - asciioffset + shift) % LETTER_COUNTS;
			ciphertext[i] = temptext + asciioffset;
            printf("%c", ciphertext[i]);
		}
		else
		{
			ciphertext[i] = plaintext[i];			
		}
	}
    printf("\n");
    
}
