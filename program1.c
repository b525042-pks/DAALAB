#include <stdio.h>
#include <math.h>

struct Function
{
    char name[50];
    double value;
};

int main()
{
    double n;
    printf("Enter a sufficiently large value of n: ");
    scanf("%lf", &n);

    struct Function f[] =
        {
            {"n log2 n", n * log2(n)},
            {"12*sqrt(n)", 12 * sqrt(n)},
            {"1/n", 1 / (n)},
            {"n^log2(n)", pow(n, log2(n))},
            {"100n^2 + 6n", 100 * n * (n + 6 * n)},
            {"n^0.51", pow(n, 0.51)},
            {"n^2 - 324", (n * n) - 324},
            {"50n^0.5", 50 * pow(n, 0.5)},
            {"2n^3", 2 * pow(n, 3)},
            {"3^n", pow(3, n)},
            {"2^32(n)", pow(2, 32) * n},
            {"log2 n", log2(n)},

        };

    int size = sizeof(f) / sizeof(f[0]);

    // Bubble Sort 
    
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - 1 - i; j++)
        {
            if (f[j].value > f[j + 1].value)
            {
                struct Function temp = f[j];
                f[j] = f[j + 1];
                f[j + 1] = temp;
            }
        }
    }

    printf("\nFunctions in Ascending Order:\n\n");
    for (int i = 0; i < size; i++)
    {
        printf("%-15s = %.4e\n", f[i].name, f[i].value);
    }

    return 0;
}