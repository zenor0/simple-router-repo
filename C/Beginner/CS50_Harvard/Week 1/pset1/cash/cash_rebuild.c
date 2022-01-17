#include<stdio.h>
#include<math.h>


int main(void)
{
    //input function
    float dollar;
    scanf("%f", &dollar);
    int cent = dollar * 100;            //cent was used to do further calculations
    printf("fetched:%f,and cents:%i\n", dollar, cent);


    //use % to deal the problem
    //use the function ceil() 
    int cent_count[3];      //order is 25, 10, 5, 1
    int cent_value[3] = {5, 2, 1};
    int decoy = cent;

    for (int i = 0; i < 3; i++)
    {
        cent_count[i] = ceil(decoy / cent_value[i]);
        decoy = decoy - cent_count[i] * cent_value[i];
    }

    //output moudle
    printf("Here is the result:\nYou will receive\n");

    for (int i = 0; i < 3; i++)
    {
        printf("%i cent: %i\n", cent_value[i], cent_count[i]);
    }

}
