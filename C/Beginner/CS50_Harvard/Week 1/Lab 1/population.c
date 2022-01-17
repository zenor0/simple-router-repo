#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // TODO: Prompt for start size
    int StartSize;
    do
    {
        StartSize = get_int("Strat size: ");
    }
    while (StartSize < 9);

    // TODO: Prompt for end size
    int EndSize;
    do
    {
        EndSize = get_int("End size: ");
    }
    while (EndSize < StartSize);

    // TODO: Calculate number of years until we reach threshold
    int n = 0;
    int TempSize = StartSize;
    while (TempSize < EndSize)
    {
        int growth = TempSize / 3;
        int death = TempSize / 4;
        TempSize = TempSize + growth - death;
        n++;
    }

    // TODO: Print number of years
    printf("Years: %i\n", n);
}
