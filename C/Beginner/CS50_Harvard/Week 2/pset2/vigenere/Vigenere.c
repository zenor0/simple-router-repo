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
    for (int i = 0; i < arglength; i++)	//check if letter
    {
		if (! isalpha(argv[1][i]))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }
    
    //initialize variables
    
    string plaintext = get_string("plaintext:");
	int plaintextLength = strlen(plaintext);
	int strlength = strlen(plaintext);
	int temptext;
	int asciioffset;
	int shift[plaintextLength];
	
    //argument pre-process    
    // upper the argument!
    for (int i = 0; i < arglength; i++)
    {
		argv[1][i] = toupper(argv[1][i]);
	}
	
	//transfer the KEY word to an array of shift key
	for (int i = 0, j = 0; i < plaintextLength; i++, j++)
	{
		if (i % arglength == 0)
		{
			j = 0;
		}
		shift[i] = argv[1][j] - UPPERCASE_LETTERS_START;
	}
    

	
	
	
    printf("ciphertext:");

	for (int i = 0; i < plaintextLength ; i++)
	{
		if(isalpha(plaintext[i]))
		{
			asciioffset = isupper(plaintext[i]) ? UPPERCASE_LETTERS_START : LOWERCASE_LETTERS_START;
			temptext = (plaintext[i] - asciioffset + shift[i]) % LETTER_COUNTS;
            printf("%c", temptext + asciioffset);
		}
		else
		{
			printf("%c", plaintext[i]);			
		}
	}
    printf("\n");
    
}
