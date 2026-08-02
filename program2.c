#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    FILE *file = fopen("coin.dat", "w");

    if (file == NULL)
    {
        printf("Error opening file!\n");
        return 1;
    }

    int tosses;
    double bias;

    printf("Enter number of tosses: ");
    scanf("%d", &tosses);

    printf("Enter bias (0 to 1): ");
    scanf("%lf", &bias);

    if (bias < 0 || bias > 1)
    {
        printf("Invalid bias!\n");
        return 1;
    }

    int fairHeads = 0, fairTails = 0;
    int biasedHeads = 0, biasedTails = 0;

    srand(time(NULL));

    for (int i = 1; i <= tosses; i++)
    {
        // Fair Coin
        if (rand() % 2 == 0)
            fairHeads++;
        else
            fairTails++;

        // Biased Coin
        double randomValue = (double)rand() / RAND_MAX;

        if (randomValue < bias)
            biasedHeads++;
        else
            biasedTails++;

        fprintf(file, "%d %.4f %.4f\n",
                i,
                (double)fairHeads / i,
                (double)biasedHeads / i);
    }

    fclose(file);

    printf("\n========== SIMULATION RESULT ==========\n");

    printf("\nFair Coin (P(Head) = 0.5)\n");
    printf("Heads = %d\n", fairHeads);
    printf("Tails = %d\n", fairTails);
    printf("Probability of Head = %.4f\n", (double)fairHeads / tosses);

    printf("\nBiased Coin (P(Head) = %.2f)\n", bias);
    printf("Heads = %d\n", biasedHeads);
    printf("Tails = %d\n", biasedTails);
    printf("Probability of Head = %.4f\n", (double)biasedHeads / tosses);


    // "C:\Program Files\gnuplot\bin\gnuplot.exe" coin.plt for simulation of graph 
    
    printf("\nSimulation completed.\n");
    printf("Data saved in coin.dat\n");

    return 0;
}

