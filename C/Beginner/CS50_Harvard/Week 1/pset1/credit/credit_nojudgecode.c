#include <cs50.h>
#include <stdio.h>
#include <string.h>
  
int main (void)
{
    //number as a number, deal it by math solution
    //or regard the imput as a string, deal it by array of characters
    //here goes first solution.

    long credit_number = get_long("Number:\n");

    //pull out every digits, save it as an array
    //这里用while 更好吧... 反正中间的条件没用上
    //局部变量 digit_count 在后面的校验里还有用..
    /* 
	for (int digit_count = 1; credit_number > 0; credit_number /= 10, digit_count++)
    {
    	//get last digit
		tempDigit = credit_number % 10;	
		
		//sum up logic
		if (digit_count % 2)
		{
			Sum_odds += tempDigit;
		}
		else 
		{
			tempDigit *= 2;		
			if (tempDigit > 10)
			{
				Sum_evens += 1;
			}
			Sum_evens += tempDigit % 10;
		}
	}
	*/
	
	int Sum_odds = 0;
	int Sum_evens = 0;
	int tempDigit = 0;
	int digit_count = 1; //初始化用1计数, 好辨认..
	
	while (credit_number > 0)
	{

		tempDigit = credit_number % 10;	
		if (digit_count % 2)
		{
			Sum_odds += tempDigit;
		}
		else 
		{
			tempDigit *= 2;	
			Sum_evens += (tempDigit / 10) + (tempDigit % 10);
		}
		
		credit_number /= 10;
		digit_count++;
	}
	//judge valid
	int checksum = Sum_evens + Sum_odds;
	bool is_valid = checksum % 10 == 0;
	if (is_valid)
	{
		printf("vaild\n");
	}
	else
	{
		printf("invaild\n");
	}
	
}

