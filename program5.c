#include <stdio.h>

int main()
{
    int n;

    printf("Enter size of array: ");
    scanf("%d", &n);

    int a[n];

    printf("Enter array elements (0's followed by 1's):\n");
    for(int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }

    int low = 0, high = n - 1;
    int idx = -1;

    // binary search algorithm

    while(low <= high)
    {
        int mid = (low + high) / 2;

        if(a[mid] == 1)
        {
            idx = mid;
            high = mid - 1;
        }
        else
        {
            low = mid + 1;
        }
    }

    if(idx == -1)
        printf("No transition point (All elements are 0).\n");
    else
        printf("Transition point is at index %d\n", idx);

    return 0;
}