#include <stdio.h>
#include <stdlib.h>

// Macro for maximum of two integers
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int min_candies(int* ratings, int n) {
    if (n == 0) return 0;

    // Allocate candy array and initialize base condition (min 1 candy)
    int* candies = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        candies[i] = 1;
    }

    // 1. Left-to-Right Pass (satisfy left neighbor constraints)
    for (int i = 1; i < n; i++) {
        if (ratings[i] > ratings[i - 1]) {
            candies[i] = candies[i - 1] + 1;
        }
    }

    // 2. Right-to-Left Pass (satisfy right neighbor constraints)
    for (int i = n - 2; i >= 0; i--) {
        if (ratings[i] > ratings[i + 1]) {
            candies[i] = MAX(candies[i], candies[i + 1] + 1);
        }
    }

    // 3. Sum total candies
    int total_candies = 0;
    for (int i = 0; i < n; i++) {
        total_candies += candies[i];
    }

    free(candies);
    return total_candies;
}

int main() {
    // Test Case 1: Increasing-decreasing peak
    int ratings1[] = {1, 0, 2};
    int n1 = sizeof(ratings1) / sizeof(ratings1[0]);
    printf("Ratings: [1, 0, 2] -> Min Candies: %d\n", min_candies(ratings1, n1));
    // Expected: 2 + 1 + 2 = 5

    // Test Case 2: Consecutive identical ratings
    int ratings2[] = {1, 2, 2};
    int n2 = sizeof(ratings2) / sizeof(ratings2[0]);
    printf("Ratings: [1, 2, 2] -> Min Candies: %d\n", min_candies(ratings2, n2));
    // Expected: 1 + 2 + 1 = 4 (Third child gets 1 because 2 is not strictly > 2)
    
    // Test Case 3: Long descending slope
    int ratings3[] = {5, 4, 3, 2, 1};
    int n3 = sizeof(ratings3) / sizeof(ratings3[0]);
    printf("Ratings: [5, 4, 3, 2, 1] -> Min Candies: %d\n", min_candies(ratings3, n3));
    // Expected: 5 + 4 + 3 + 2 + 1 = 15

    return 0;
}