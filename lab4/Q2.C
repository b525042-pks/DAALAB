/*
Question 2:
Application of sorting-II: Given two sets S1 and S2 (each of size n), and a number x,
describe an O(n · logn) algorithm for finding whether there exists a pair of elements,
one from S1 and one from S2, that add up to x. By choosing the proper input
representation, write a program in C to validate your algorithm.

Algorithm:
1. Sort one of the sets (say S2) in ascending order. This takes O(n log n).
2. For each element a in S1:
   - Compute target = x - a
   - Binary search for target in the sorted S2 (O(log n))
   - If found, we have a pair (a, target) with a ∈ S1, target ∈ S2, and a + target = x
3. If no such pair is found after checking all elements of S1, report failure.

Complexity:
- Total time: O(n log n)
- Extra space: O(1) beyond input arrays

Pseudocode:
Algorithm ExistsPairSum(S1[1..n], S2[1..n], x):
    Input:  S1, S2 = two sets of n integers each
            x = target sum
    Output: A pair (a, b) with a ∈ S1, b ∈ S2, a + b = x, or report none exists
    1. Sort S2 in ascending order
    2. For i = 1 to n:
           a ← S1[i]
           target ← x - a
           If BinarySearch(S2, target) = true:
               Return (a, target)
    3. Return "No pair found"
Function BinarySearch(A[1..n], target):
    Input:  A = sorted array of n integers
            target = value to search for
    Output: true if target ∈ A, else false
    1. left ← 1
       right ← n
    2. While left ≤ right:
           mid ← left + (right - left) / 2
           If A[mid] = target:
               Return true
           Else if A[mid] < target:
               left ← mid + 1
           Else:
               right ← mid - 1

    3. Return false
*/


// CODE---
#include <stdio.h>
void merge(int a[], int low, int mid, int high)
{
    int i = low;
    int j = mid + 1;
    int k = 0;
    int temp[high - low + 1];
    while (i <= mid && j <= high)
    {
        if (a[i] < a[j])
        {
            temp[k++] = a[i++];
        }
        else
        {
            temp[k++] = a[j++];
        }
    }
    while (i <= mid)
    {
        temp[k++] = a[i++];
    }
    while (j <= high)
    {
        temp[k++] = a[j++];
    }
    for (i = low, k = 0; i <= high; i++, k++)
    {
        a[i] = temp[k];
    }
}
void mergeSort(int a[], int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;

        mergeSort(a, low, mid);
        mergeSort(a, mid + 1, high);

        merge(a, low, mid, high);
    }
}
int binarySearch(int a[], int n, int key)
{
    int low = 0;
    int high = n - 1;
    while (low <= high)
    {
        int mid = (low + high) / 2;

        if (a[mid] == key)
        {
            return 1;
        }
        else if (a[mid] < key)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }
    return 0;
}
int main()
{
    int n, x;

    printf("Enter size of both sets: ");
    scanf("%d", &n);

    int S1[n], S2[n];

    printf("Enter elements of S1:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &S1[i]);
    }

    printf("Enter elements of S2:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &S2[i]);
    }

    printf("Enter target value x: ");
    scanf("%d", &x);
    // Sort S2 using Merge Sort
    mergeSort(S2, 0, n - 1);
    printf("\nSorted S2: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", S2[i]);
    }
    // For every element of S1, search for x - S1[i]
    for (int i = 0; i < n; i++)
    {
        int required = x - S1[i];

        if (binarySearch(S2, n, required))
        {
            printf("\n\nPair found: %d + %d = %d\n",
                   S1[i], required, x);

            printf("YES, such a pair exists.\n");

            return 0;
        }
    }
    printf("\n\nNO, such a pair does not exist.\n");
    return 0;
}