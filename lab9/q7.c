#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))

// --------------------------------------------------------
// Max-Heap Implementation (1-based indexing)
// --------------------------------------------------------
void push_heap(int* heap, int* size, int val) {
    int i = ++(*size);
    while (i > 1 && heap[i / 2] < val) {
        heap[i] = heap[i / 2];
        i /= 2;
    }
    heap[i] = val;
}

int pop_heap(int* heap, int* size) {
    if (*size == 0) return 0;
    int max_val = heap[1];
    int temp = heap[(*size)--];
    int i = 1, child = 2;
    
    while (child <= *size) {
        if (child < *size && heap[child + 1] > heap[child]) {
            child++;
        }
        if (temp >= heap[child]) break;
        heap[i] = heap[child];
        i = child;
        child *= 2;
    }
    heap[i] = temp;
    return max_val;
}

// --------------------------------------------------------
// Core Algorithm
// --------------------------------------------------------
int minimum_deviation(int* nums, int n) {
    if (n <= 1) return 0;

    int* heap = (int*)malloc((n + 1) * sizeof(int));
    int heap_size = 0;
    int min_val = INT_MAX;

    // 1. Normalize array (multiply odds by 2) and find initial minimum
    for (int i = 0; i < n; i++) {
        int val = nums[i];
        if (val % 2 != 0) {
            val *= 2;
        }
        push_heap(heap, &heap_size, val);
        if (val < min_val) {
            min_val = val;
        }
    }

    int min_deviation = INT_MAX;

    // 2. Greedy reduction
    while (1) {
        int max_val = pop_heap(heap, &heap_size);
        
        // Update the minimum deviation found so far
        int current_deviation = max_val - min_val;
        if (current_deviation < min_deviation) {
            min_deviation = current_deviation;
        }

        // If the max element is odd, we cannot divide it anymore
        if (max_val % 2 != 0) {
            break;
        }

        // Divide by 2, update global minimum, and push back
        max_val /= 2;
        min_val = MIN(min_val, max_val);
        push_heap(heap, &heap_size, max_val);
    }

    free(heap);
    return min_deviation;
}

int main() {
    // Test Case 1
    int nums1[] = {1, 2, 3, 4};
    int n1 = sizeof(nums1) / sizeof(nums1[0]);
    printf("Array: [1, 2, 3, 4]\nMinimum Deviation: %d\n\n", minimum_deviation(nums1, n1));
    // Expected: 1 (Transform to [2, 2, 3, 2], max=3, min=2, diff=1)

    // Test Case 2
    int nums2[] = {4, 1, 5, 20, 3};
    int n2 = sizeof(nums2) / sizeof(nums2[0]);
    printf("Array: [4, 1, 5, 20, 3]\nMinimum Deviation: %d\n", minimum_deviation(nums2, n2));
    // Expected: 3 (Transform to [4, 2, 5, 5, 6], max=6, min=2) -> divide 6 by 2 -> max=5, min=2 -> divide 4 -> max=5, min=2. Deviation = 5 - 2 = 3.

    return 0;
}