// QUESTION 1:
// Binary vs Ternary Search: In binary search, an n element list is divided into nearly two
// equal halves, while in ternary search, it is divided into nearly three equal intervals.
// Then the search will be in one of the intervals. Design and implement a C program to 
// search for an element x in a sorted list of size n using binary and ternary search. 
// Justify and validate that binary search is better than ternary search via your 
// implementation.


//code:-------
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Binary Search
int binarySearch(int arr[], int n, int x, int *comparisons)
{
    int low = 0;
    int high = n - 1;

    while (low <= high)
    {
        int mid = low + (high - low) / 2;

        (*comparisons)++;

        if (arr[mid] == x)
            return mid;

        if (x < arr[mid])
            high = mid - 1;
        else
            low = mid + 1;
    }

    return -1;
}

// Ternary Search
int ternarySearch(int arr[], int n, int x, int *comparisons)
{
    int low = 0;
    int high = n - 1;

    while (low <= high)
    {
        int third = (high - low) / 3;

        int mid1 = low + third;
        int mid2 = high - third;

        (*comparisons)++;

        if (arr[mid1] == x)
            return mid1;

        (*comparisons)++;

        if (arr[mid2] == x)
            return mid2;

        if (x < arr[mid1])
        {
            high = mid1 - 1;
        }
        else if (x > arr[mid2])
        {
            low = mid2 + 1;
        }
        else
        {
            low = mid1 + 1;
            high = mid2 - 1;
        }
    }

    return -1;
}

int main()
{   
    printf("program started\n");
    int n, x;

    int arr[1000];

    int binaryComparisons = 0;
    int ternaryComparisons = 0;

    printf("Enter size of array: ");
    scanf("%d", &n);

    if (n <= 0 || n > 1000000)
    {
        printf("Invalid array size.\n");
        return 1;
    }

    printf("Enter %d sorted elements:\n", n);

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    printf("Enter element to search: ");
    scanf("%d", &x);

    // Binary Search
    int b = binarySearch(arr, n, x, &binaryComparisons);

    // Ternary Search
    int t = ternarySearch(arr, n, x, &ternaryComparisons);

    // Binary Search result
    printf("\n--- Binary Search ---\n");

    if (b != -1)
        printf("Element found at index %d\n", b);
    else
        printf("Element not found\n");

    printf("Comparisons = %d\n", binaryComparisons);

    // Ternary Search result
    printf("\n--- Ternary Search ---\n");

    if (t != -1)
        printf("Element found at index %d\n", t);
    else
        printf("Element not found\n");

    printf("Comparisons = %d\n", ternaryComparisons);

    // Compare both searches
    if (binaryComparisons < ternaryComparisons)
    {
        printf("\nBinary Search is better for this search.\n");
    }
    else if (binaryComparisons > ternaryComparisons)
    {
        printf("\nTernary Search is better for this search.\n");
    }
    else
    {
        printf("\nBoth performed the same number of comparisons.\n");
    }

    // Store result in file
    FILE *fp;

    fp = fopen("comparison.dat", "w");

    if (fp == NULL)
    {
        printf("Error opening comparison.dat\n");
        return 1;
    }

    fprintf(fp, "%d\t%d\t%d\n",
            n, binaryComparisons, ternaryComparisons);

    fclose(fp);

    printf("\nData saved to comparison.dat\n");

    return 0;
}
