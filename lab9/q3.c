#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int dist; // Distance from origin
    int fuel; // Amount of fuel available at this station
} Station;

// Comparator to sort stations by distance from the origin
int compare_stations(const void* a, const void* b) {
    return ((Station*)a)->dist - ((Station*)b)->dist;
}

// --------------------------------------------------------
// Max-Heap Implementation for C
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
    if (*size == 0) return -1;
    int max_val = heap[1];
    int temp = heap[(*size)--];
    int i = 1, child = 2;
    
    while (child <= *size) {
        if (child < *size && heap[child + 1] > heap[child]) child++;
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
int min_refuel_stops(int target, int start_fuel, Station* stations, int n) {
    // 1. Sort stations by distance
    qsort(stations, n, sizeof(Station), compare_stations);

    // 2. Initialize variables and max-heap
    int* heap = (int*)malloc((n + 1) * sizeof(int));
    int heap_size = 0;
    
    int stops = 0;
    int current_fuel = start_fuel;
    int current_pos = 0;

    // Iterate through all stations + the final destination target
    for (int i = 0; i <= n; i++) {
        // The final "station" to reach is the target itself
        int next_pos = (i < n) ? stations[i].dist : target;
        int distance_to_cover = next_pos - current_pos;

        // While we don't have enough fuel to reach the next coordinate
        while (current_fuel < distance_to_cover) {
            if (heap_size == 0) {
                free(heap);
                return -1; // Unreachable
            }
            // Retroactively take the largest fuel we passed
            current_fuel += pop_heap(heap, &heap_size);
            stops++;
        }

        // Move to the next coordinate
        current_fuel -= distance_to_cover;
        current_pos = next_pos;

        // Remember the fuel at the current station
        if (i < n) {
            push_heap(heap, &heap_size, stations[i].fuel);
        }
    }

    free(heap);
    return stops;
}

int main() {
    int target = 100;
    int start_fuel = 10;
    
    // Stations array: {distance_from_start, fuel_capacity}
    Station stations[] = {
        {10, 60}, 
        {20, 30}, 
        {30, 30}, 
        {60, 40}
    };
    int n = sizeof(stations) / sizeof(stations[0]);

    int result = min_refuel_stops(target, start_fuel, stations, n);
    
    if (result == -1) {
        printf("Target is unreachable.\n");
    } else {
        printf("Minimum number of refueling stops required: %d\n", result);
    }

    return 0;
}