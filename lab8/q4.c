#include <stdio.h>
int main()
{
    int A[100], dp[100], parent[100];
    int n, i, j;
    int maxLength = 1;
    int last;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    printf("Enter the elements:\n");
    for (i = 0; i < n; i++)
    {
        scanf("%d", &A[i]);
        dp[i] = 1;
        parent[i] = -1;
    }
    for (i = 1; i < n; i++)
    {
        for (j = 0; j < i; j++)
        {
            if (A[j] < A[i] && dp[j] + 1 > dp[i])
            {
                dp[i] = dp[j] + 1;
                parent[i] = j;
            }
        }
        if (dp[i] > maxLength)
        {
            maxLength = dp[i];
            last = i;
        }
    }
    printf("Length of LIS = %d\n", maxLength);
    printf("LIS = ");
    int lis[100];
    int k = 0;
    while (last != -1)
    {
        lis[k++] = A[last];
        last = parent[last];
    }
    for (i = k - 1; i >= 0; i--)
    {
        printf("%d ", lis[i]);
    }
    printf("\n");
    return 0;
}