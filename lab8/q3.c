#include <stdio.h>
#include <string.h>
#define MAX 100
int max(int a, int b)
{
    return (a > b) ? a : b;
}
int main()
{
    char X[MAX], Y[MAX];
    int L[MAX + 1][MAX + 1];
    int m, n;
    int i, j;
    printf("Enter first sequence: ");
    scanf("%s", X);
    printf("Enter second sequence: ");
    scanf("%s", Y);
    m = strlen(X);
    n = strlen(Y);
    for (i = 0; i <= m; i++)
    {
        L[i][0] = 0;
    }
    for (j = 0; j <= n; j++)
    {
        L[0][j] = 0;
    }
    for (i = 1; i <= m; i++)
    {
        for (j = 1; j <= n; j++)
        {
            if (X[i - 1] == Y[j - 1])
            {
                L[i][j] = L[i - 1][j - 1] + 1;
            }
            else
            {
                L[i][j] = max(L[i - 1][j], L[i][j - 1]);
            }
        }
    }
    int length = L[m][n];
    printf("\nLength of LCS = %d\n", length);
    char lcs[MAX];
    lcs[length];
    i = m;
    j = n;
    int index = length - 1;
    while (i > 0 && j > 0)
    {
        if (X[i - 1] == Y[j - 1])
        {
            lcs[index] = X[i - 1];
            i--;
            j--;
            index--;
        }
        else if (L[i - 1][j] > L[i][j - 1])
        {
            i--;
        }
        else
        {
            j--;
        }
    }
    printf("LCS = %s\n", lcs);
    return 0;
}