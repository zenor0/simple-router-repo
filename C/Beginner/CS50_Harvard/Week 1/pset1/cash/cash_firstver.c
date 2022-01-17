#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //input function
    float dollar = 0.78;
    int cent = dollar * 100;
    printf("fetched:%f,and cents:%i\n", dollar, cent);

    //calculate function
    int count_cent25 = 0;
    int count_cent10 = 0;
    int count_cent5 = 0;
    int count_cent1 = 0;

    for (int decoy = cent; decoy > 0; )
    {
        if(decoy >= 25)
        {
            count_cent25++;
            decoy = decoy - 25;
        }
        else if (decoy >= 10)
        {
            count_cent10++;
            decoy = decoy - 10;
        }
        else if (decoy >= 5)
        {
            count_cent5++;
            decoy = decoy - 5;
        }
        else if (decoy >= 1)
        {
            count_cent1++;
            decoy = decoy - 1;
        }
    }


    //output function
    printf("you owed: $%.2f, as well as %i cents\n", dollar, cent);
    printf("you will have\n25cent: %i\n10cent: %i\n5cent: %i\n1cent: %i", count_cent25, count_cent10, count_cent5, count_cent1);


}
