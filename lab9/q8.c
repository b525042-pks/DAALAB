#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

// Proper input representation
typedef struct {
    int start;
    int end;
} Interval;

// Comparator for qsort
int compare_ints(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

// Core Algorithm
int min_meeting_rooms(Interval* intervals, int n) {
    if (n == 0) return 0;

    // 1. Decouple start and end times
    int* starts = (int*)malloc(n * sizeof(int));
    int* ends = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        starts[i] = intervals[i].start;
        ends[i] = intervals[i].end;
    }

    // 2. Chronological sorting
    qsort(starts, n, sizeof(int), compare_ints);
    qsort(ends, n, sizeof(int), compare_ints);

    // 3. Two-pointer timeline sweep
    int active_rooms = 0;
    int max_rooms = 0;
    int s_ptr = 0;
    int e_ptr = 0;

    while (s_ptr < n) {
        // If a meeting starts before the earliest ending meeting ends, we need a room
        if (starts[s_ptr] < ends[e_ptr]) {
            active_rooms++;
            max_rooms = MAX(max_rooms, active_rooms);
            s_ptr++;
        } 
        // Otherwise, a meeting ends and frees a room
        else {
            active_rooms--;
            e_ptr++;
        }
    }

    free(starts);
    free(ends);

    return max_rooms;
}

int main() {
    // Test Case 1: Overlapping intervals
    Interval intervals1[] = {{0, 30}, {5, 10}, {15, 20}};
    int n1 = sizeof(intervals1) / sizeof(intervals1[0]);
    printf("Intervals: [[0, 30], [5, 10], [15, 20]]\n");
    printf("Minimum meeting rooms: %d\n\n", min_meeting_rooms(intervals1, n1));
    // Expected Output: 2

    // Test Case 2: Non-overlapping intervals
    Interval intervals2[] = {{7, 10}, {2, 4}};
    int n2 = sizeof(intervals2) / sizeof(intervals2[0]);
    printf("Intervals: [[7, 10], [2, 4]]\n");
    printf("Minimum meeting rooms: %d\n\n", min_meeting_rooms(intervals2, n2));
    // Expected Output: 1
    
    // Test Case 3: Back-to-back meetings
    Interval intervals3[] = {{1, 5}, {5, 9}, {9, 12}};
    int n3 = sizeof(intervals3) / sizeof(intervals3[0]);
    printf("Intervals: [[1, 5], [5, 9], [9, 12]]\n");
    printf("Minimum meeting rooms: %d\n", min_meeting_rooms(intervals3, n3));
    // Expected Output: 1

    return 0;
}