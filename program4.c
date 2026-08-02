#include <stdio.h>
#include <math.h>

int main()
{
    FILE *file = fopen("toh.dat", "w");

    if(file == NULL)
    {
        printf("Error opening file!\n");
        return 1;
    }

    int Discs;

    printf("Enter  number of discs: ");
    scanf("%d", &Discs);

    printf("\nDiscs\tMoves\n");
    printf("-------------------\n");

    for(int n = 1; n <= Discs; n++)
    {
        long long moves = pow(2,n) - 1;

        printf("%d\t%lld\n", n, moves);
        fprintf(file, "%d %lld\n", n, moves);
    }

    fclose(file);

    printf("\nData saved in toh.dat\n");

    return 0;
}