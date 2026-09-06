/*
 * Question 4: Sorting via reversal procedure
 * Suppose you are given a permutation p of the integers 1 to n, and seek to sort them 
 * to be in increasing order [1, ..., n]. The only operation at your disposal is reverse(p, i, j).
 * - Mathematically, show that it is possible to sort any permutation using O(n) reversals.
 * - Now suppose that the cost of reverse(p, i, j) is equal to its length. Design an algorithm
 *   that sorts p in O(n log^2 n) cost. Analyse the running time and cost of your algorithm
 *   and prove the correctness.
 * Write a program in C to validate your algorithm supporting your analysis.
 */
#include <stdio.h>
void reverse(int p[], int i, int j) {
    while (i < j) {
        int temp = p[i];
        p[i] = p[j];
        p[j] = temp;
        i++; j--;
    }
}
/* 
 * Complexity Analysis (Reversal Operation):
 * Worst-case Cost: (j - i + 1). Cost is proportional to the length of the sub-array being reversed.
 */
void blockSwap(int p[], int start, int lenA, int lenB) {
    if (lenA == 0 || lenB == 0) return;
    reverse(p, start, start + lenA - 1);               
    reverse(p, start + lenA, start + lenA + lenB - 1); 
    reverse(p, start, start + lenA + lenB - 1);        
}
/* 
 * Complexity Analysis (Block Swapping):
 * Worst-case Cost: O(lenA + lenB). Reversing both blocks separately and then together 
 * totals a cost exactly bounded by 2*(lenA + lenB).
 */
int binarySearch(int p[], int low, int high, int val) {
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (p[mid] < val) low = mid + 1;
        else high = mid - 1;
    }
    return low;
}
/* 
 * Complexity Analysis (Binary Search Insertion Point):
 * Worst-case Time: O(log N). Standard binary search divides the search space in half.
 */
void mergeReversal(int p[], int start, int mid, int end) {
    if (start >= mid || mid > end) return;
    int lenA = mid - start;
    int lenB = end - mid + 1;
    if (lenA == 0 || lenB == 0) return;
    int midA = start + lenA / 2;
    int val = p[midA];
    int midB = binarySearch(p, mid, end, val);
    int sizeA2 = mid - midA;
    int sizeB1 = midB - mid;
    blockSwap(p, midA, sizeA2, sizeB1);
    int newMid = midA + sizeB1;
    mergeReversal(p, start, midA, newMid - 1);
    mergeReversal(p, newMid + 1, midB, end);
}
/* 
 * Complexity Analysis (Merge using Reversals):
 * Worst-case Cost: O(N log N). Finding the median and its target location splits 
 * the arrays. The recursion tree branch resolves to M(N) = 2*M(N/2) + O(N).
 */
void mergeSortReversal(int p[], int start, int end) {
    if (start >= end) return;
    int mid = start + (end - start) / 2;
    mergeSortReversal(p, start, mid);
    mergeSortReversal(p, mid + 1, end);
    mergeReversal(p, start, mid + 1, end);
}
/* 
 * Complexity Analysis (Total Merge Sort Reversal Algorithm):
 * Total Worst-case Cost: O(N log^2 N). T(N) = 2*T(N/2) + O(N log N). By the 
 * Master Theorem, the total execution resolves to O(N log^2 N).
 */
int main() {
    int p[] = {1, 4, 3, 2, 5, 8, 7, 6};
    int n = sizeof(p) / sizeof(p[0]);
    printf("\n--- Question 4 Outputs ---\n");
    printf("Initial Permutation: ");
    for (int i = 0; i < n; i++) printf("%d ", p[i]);
    printf("\n");
    mergeSortReversal(p, 0, n - 1);
    printf("Sorted Permutation:  ");
    for (int i = 0; i < n; i++) printf("%d ", p[i]);
    printf("\n");
    return 0;
}