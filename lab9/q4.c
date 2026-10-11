#include <stdio.h>
#include <stdlib.h>

// --------------------------------------------------------
// Min-Heap Implementation for C (1-based indexing)
// --------------------------------------------------------
void push_heap(int* heap, int* size, int val) {
    int i = ++(*size);
    // Bubble up
    while (i > 1 && heap[i / 2] > val) {
        heap[i] = heap[i / 2];
        i /= 2;
    }
    heap[i] = val;
}

int pop_heap(int* heap, int* size) {
    if (*size == 0) return 0;
    
    int min_val = heap[1];
    int temp = heap[(*size)--];
    int i = 1, child = 2;
    
    // Bubble down
    while (child <= *size) {
        // Select the smaller of the two children
        if (child < *size && heap[child + 1] < heap[child]) {
            child++;
        }
        if (temp <= heap[child]) {
            break;
        }
        heap[i] = heap[child];
        i = child;
        child *= 2;
    }
    heap[i] = temp;
    return min_val;
}

// --------------------------------------------------------
// Core Algorithm
// --------------------------------------------------------
int min_cost_to_connect_sticks(int* sticks, int n) {
    if (n <= 1) return 0;

    // Allocate heap (1-based index requires n + 1 size)
    int* heap = (int*)malloc((n + 1) * sizeof(int));
    int heap_size = 0;

    // 1. Build the Min-Heap
    for (int i = 0; i < n; i++) {
        push_heap(heap, &heap_size, sticks[i]);
    }

    int total_cost = 0;

    // 2. Greedy combination process
    while (heap_size > 1) {
        // Extract the two smallest sticks
        int stick1 = pop_heap(heap, &heap_size);
        int stick2 = pop_heap(heap, &heap_size);

        // Combine them
        int combined = stick1 + stick2;
        total_cost += combined;

        // Push the combined stick back into the heap
        push_heap(heap, &heap_size, combined);
    }

    free(heap);
    return total_cost;
}

int main() {
    // Example test case
    // Expected combination: (2+3)=5 (cost 5), (4+5)=9 (cost 9) -> Total 14
    int sticks[] = {2, 4, 3};
    int n = sizeof(sticks) / sizeof(sticks[0]);

    int result = min_cost_to_connect_sticks(sticks, n);
    
    printf("Lengths: ");
    for (int i = 0; i < n; i++) printf("%d ", sticks[i]);
    printf("\nMinimum cost to connect all sticks: %d\n", result);

    // Larger test case: {1, 8, 3, 5}
    // (1+3)=4 (cost 4), (4+5)=9 (cost 9), (8+9)=17 (cost 17) -> Total 30
    int sticks2[] = {1, 8, 3, 5};
    int n2 = sizeof(sticks2) / sizeof(sticks2[0]);
    printf("\nLengths: ");
    for (int i = 0; i < n2; i++) printf("%d ", sticks2[i]);
    printf("\nMinimum cost to connect all sticks: %d\n", min_cost_to_connect_sticks(sticks2, n2));

    return 0;
}