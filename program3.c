#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int bubblemodified(int a[], int n)
{
    int comp = 0, temp, swapped;

    for (int i = 0; i < n - 1; i++)
    {
        swapped = 0;

        for (int j = 0; j < n - i - 1; j++)
        {
            comp++;
            if (a[j] > a[j + 1])
            {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
                swapped = 1;
            }
        }

        if (swapped == 0)
            break;
    }

    return comp;
}

int bubbleNormal(int a[], int n)
{
    int comp = 0, temp;

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            comp++;

            if (a[j] > a[j + 1])
            {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }

    return comp;
}

int main()
{
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int a[n], b[n];

    srand(time(NULL));

    // Generate random numbers
    for (int i = 0; i < n; i++)
    {
        a[i] = rand() % 100;
        b[i] = a[i];
    }
    printf("array before sorting:\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d ,", a[i]);
    }

    int c1 = bubblemodified(a, n);
    int c2 = bubbleNormal(b, n);

    printf("\nmodified Bubble Sort Comparisons = %d\n", c1);
    printf("\nNormal Bubble Sort Comparisons    = %d\n", c2);
    printf(" array after sorting :\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d ,", a[i]);
    }
     
    //"C:\Program Files\gnuplot\bin\gnuplot.exe" bubble_compare.plt for simulation
    // Save data for gnuplot
    FILE *fp = fopen("bubble_compare.dat", "w");
    fprintf(fp, "modified %d\n", c1);
    fprintf(fp, "Normal %d\n", c2);
    fclose(fp);

    printf("\n\nData saved to bubble_compare.dat\n");

    return 0;
}