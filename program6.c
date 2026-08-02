#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
    int n;

    printf("Enter the number of random numbers: ");
    scanf("%d", &n);

    int a[n];

    srand(time(NULL));

    printf("\nRandom Numbers:\n");

    for(int i = 0; i < n; i++)
    {
        a[i] = rand() % 100;      // Random numbers from 0 to 99
        printf("%d ", a[i]);
    }

    int found = 0;

    for(int i = 0; i < n - 1; i++)
    {
        for(int j = i + 1; j < n; j++)
        {
            if(a[i] == a[j])
            {
                printf("\n\nDuplicate found: %d", a[i]);
                found = 1;
                break;
            }
        }

        if(found)
            break;
    }

    if(!found)
        printf("\n\nNo duplicates found.");

    return 0;
}