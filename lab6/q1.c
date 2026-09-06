/*
 * Question 1: 1D array operations and their complexities
 * Given an array with n unsorted integer elements, what is the worst-case complexity of the following problems in terms of n:
 * (i) Finding the maximum element.
 * (ii) Finding the first and second largest elements.
 * (iii) Finding the mean.
 * (iv) Finding the median.
 * (v) Finding the standard deviation.
 * (vi) Finding the mode.
 * (vii) Removing all duplicates.
 * (viii) Reversing the elements of the array.
 * (ix) Partitioning the array with respect to a given random pivot element so that all elements less than the pivot appear after all the elements greater than or equal to the pivot.
 * By choosing the proper input representation, write a program in C to validate your procedures and derive the corresponding complexity analysis.
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
int compare(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}
int findMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] > max) max = arr[i];
    }
    return max;
}
/* 
 * Complexity Analysis (Finding the maximum element):
 * Worst-case: O(n). The algorithm must inspect every element in the array exactly once.
 */
void findFirstSecondMax(int arr[], int n, int *first, int *second) {
    *first = arr[0];
    *second = -2147483648; 
    for (int i = 1; i < n; i++) {
        if (arr[i] > *first) {
            *second = *first;
            *first = arr[i];
        } else if (arr[i] > *second && arr[i] != *first) {
            *second = arr[i];
        }
    }
}
/* 
 * Complexity Analysis (Finding first and second largest elements):
 * Worst-case: O(n). Achieved in a single linear pass.
 */

double findMean(int arr[], int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) sum += arr[i];
    return sum / n;
}
/* 
 * Complexity Analysis (Finding the mean):
 * Worst-case: O(n). Requires traversing the entire array exactly once.
 */

double findMedian(int arr[], int n) {
    int *temp = malloc(n * sizeof(int));
    for(int i = 0; i < n; i++) temp[i] = arr[i];
    qsort(temp, n, sizeof(int), compare);
    double median = (n % 2 == 0) ? (temp[n/2 - 1] + temp[n/2]) / 2.0 : temp[n/2];
    free(temp);
    return median;
}
/* 
 * Complexity Analysis (Finding the median):
 * Worst-case: O(n log n). Using qsort dominates the runtime.
 */
double findStdDev(int arr[], int n) {
    double mean = findMean(arr, n);
    double varSum = 0;
    for (int i = 0; i < n; i++) varSum += pow(arr[i] - mean, 2);
    return sqrt(varSum / n);
}
/* 
 * Complexity Analysis (Finding the standard deviation):
 * Worst-case: O(n). Requires two consecutive linear passes.
 */

int findMode(int arr[], int n) {
    int *temp = malloc(n * sizeof(int));
    for(int i = 0; i < n; i++) temp[i] = arr[i];
    qsort(temp, n, sizeof(int), compare);
    int mode = temp[0], maxCount = 1, currentCount = 1;
    for (int i = 1; i < n; i++) {
        if (temp[i] == temp[i - 1]) currentCount++;
        else currentCount = 1;
        
        if (currentCount > maxCount) {
            maxCount = currentCount;
            mode = temp[i];
        }
    }
    free(temp);
    return mode;
}
/* 
 * Complexity Analysis (Finding the mode):
 * Worst-case: O(n log n). Sorting dominates the linear scan step.
 */
int removeDuplicates(int arr[], int n) {
    if (n == 0 || n == 1) return n;
    qsort(arr, n, sizeof(int), compare);
    int j = 0;
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] != arr[i + 1]) arr[j++] = arr[i];
    }
    arr[j++] = arr[n - 1];
    return j; 
}
/* 
 * Complexity Analysis (Removing all duplicates):
 * Worst-case: O(n log n). Sorting followed by a single in-place linear scan.
 */

void reverseArray(int arr[], int n) {
    for (int i = 0; i < n / 2; i++) {
        int temp = arr[i];
        arr[i] = arr[n - 1 - i];
        arr[n - 1 - i] = temp;
    }
}
/* 
 * Complexity Analysis (Reversing the elements):
 * Worst-case: O(n). Loop runs n/2 times with O(1) swaps.
 */
void partitionArray(int arr[], int n) {
    if (n == 0) return;
    int pivotIdx = rand() % n;
    int pivot = arr[pivotIdx];
    printf("(Pivot chosen: %d) ", pivot);
    int *temp = malloc(n * sizeof(int));
    int left = 0, right = n - 1;
    
    for (int i = 0; i < n; i++) {
        if (arr[i] >= pivot) temp[left++] = arr[i];
        else temp[right--] = arr[i];
    }
    for (int i = 0; i < n; i++) arr[i] = temp[i];
    free(temp);
}
/* 
 * Complexity Analysis (Partitioning the array):
 * Worst-case: O(n). A single pass to distribute elements.
 */
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
}
void copyArray(int src[], int dest[], int n) {
    for(int i = 0; i < n; i++) dest[i] = src[i];
}
int main() {
    srand(time(NULL));
    int arr[] = {4, 2, 8, 2, 1, 9, 7, 5, 8, 2};
    int n = sizeof(arr) / sizeof(arr[0]);
    int tempArr[10];
    
    printf("--- Question 1 Outputs ---\n");
    printf("Original Array: ");
    printArray(arr, n);
    // (i)
    printf("(i) Maximum Element: %d\n", findMax(arr, n));
    // (ii)
    int first, second;
    findFirstSecondMax(arr, n, &first, &second);
    printf("(ii) First Largest: %d, Second Largest: %d\n", first, second);
    // (iii)
    printf("(iii) Mean: %.2f\n", findMean(arr, n));
    // (iv)
    printf("(iv) Median: %.2f\n", findMedian(arr, n));
    // (v)
    printf("(v) Standard Deviation: %.2f\n", findStdDev(arr, n));
    // (vii)
    printf("(vi) Mode: %d\n", findMode(arr, n));
    // (viii) Modifying operation, use a copy
    copyArray(arr, tempArr, n);
    reverseArray(tempArr, n);
    printf("(viii) Reversed Array: ");
    printArray(tempArr, n);
    // (ix) Modifying operation, use a copy
    copyArray(arr, tempArr, n);
    printf("(ix) Partitioned Array: ");
    partitionArray(tempArr, n);
    printArray(tempArr, n);
    // (vii) Modifying operation that changes size, run last
    copyArray(arr, tempArr, n);
    int newSize = removeDuplicates(tempArr, n);
    printf("(vii) Array after removing duplicates: ");
    printArray(tempArr, newSize);
    return 0;
}
