#include <stdio.h>
#include <stdlib.h>
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

    if (k == pivotIndex)
        return arr[pivotIndex];

    else if (k < pivotIndex)
        return quickSelect(arr, low, pivotIndex - 1, k);

    else
        return quickSelect(arr, pivotIndex + 1, high, k);
}
int main()
{
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);
    int arr[n];
    printf("Enter elements:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }
    if (n % 2 == 1)
    {
        int median = quickSelect(arr, 0, n - 1, n / 2);
        printf("Median = %d\n", median);
    }
    else
    {
        int left=quickSelect(arr, 0, n - 1, n / 2 - 1);
        int right = quickSelect(arr, 0, n - 1, n / 2);
        double median = (left + right) / 2.0;
        printf("Median = %.2lf\n", median);
    }
    return 0;
}
