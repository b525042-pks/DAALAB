#include <stdio.h>
int main()
{
    int A[100], dp[100], parent[100];
    int n, i, j;
    int maxSum, last;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter the elements:\n");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &A[i]);
    }

    for (i = 0; i < n; i++)
    {
        dp[i] = A[i];
        parent[i] = -1;
    }
    for (i = 1; i < n; i++)
    {
        for (j = 0; j < i; j++)
        {
            if (A[j] < A[i] && dp[j] + A[i] > dp[i])
            {
                dp[i] = dp[j] + A[i];
                parent[i] = j;
            }
        }
    }
    maxSum = dp[0];
    last = 0;
    for (i = 1; i < n; i++)
    {
        if (dp[i] > maxSum)
        {
            maxSum = dp[i];
            last = i;
        }
    }

    printf("\nMaximum Sum = %d\n", maxSum);
    printf("Maximum Sum Increasing Subsequence: ");

    int sequence[100];
    int k = 0;

    while (last != -1)
    {
        sequence[k++] = A[last];
        last = parent[last];
    }

    for (i = k - 1; i >= 0; i--)
    {
        printf("%d ", sequence[i]);
    }

    printf("\n");

    return 0;
}