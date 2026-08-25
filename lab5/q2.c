#include <stdio.h>
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
int partition(int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);

    return i + 1;
}

int quickSelect(int arr[], int low, int high, int k)
{
    if (low == high)
        return arr[low];

    int pivotIndex = partition(arr, low, high);

    if (pivotIndex == k)
        return arr[pivotIndex];

    else if (k < pivotIndex)
        return quickSelect(arr, low, pivotIndex - 1, k);

    else
        return quickSelect(arr, pivotIndex + 1, high, k);
}
int main()
{
    int n, k;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter elements:\n");
    for (int i = 0; i < n; i++)
    { 
      scanf("%d", &arr[i]);
    }
    printf("Enter K: ");
    scanf("%d", &k);
    if (k < 1 || k > n)
    {
        printf("Invalid value of K\n");
        return 0;
    }
    int result = quickSelect(arr, 0, n - 1, k - 1);
    printf("%dth smallest element = %d\n", k, result);
    return 0;
}