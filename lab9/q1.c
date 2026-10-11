#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    double base_density; // v_i / w_i
    double weight;       // w_i
    double decay;        // \lambda_i
    double x;            // Chosen fractional weight
} Item;

// Sort by decay rate descending (Smith's Rule for deterioration)
int compare_decay(const void* a, const void* b) {
    Item* i1 = (Item*)a;
    Item* i2 = (Item*)b;
    if (i1->decay < i2->decay) return 1;
    if (i1->decay > i2->decay) return -1;
    return 0;
}

int main() {
    // Example test case W = 4.0
    // Item 1: density=10, weight=2, decay=2 (Fast decay)
    // Item 2: density=12, weight=2, decay=1 (Slow decay)
    int n = 2;
    double W = 4.0;
    Item items[] = {
        {1, 10.0, 2.0, 2.0, 0.0},
        {2, 12.0, 2.0, 1.0, 0.0}
    };
    
    // 1. Enforce optimal scheduling order
    qsort(items, n, sizeof(Item), compare_decay);
    
    // 2. Continuous Greedy Allocation via Marginal Benefit
    double eps = 0.0001; 
    double current_W = 0.0;
    
    while (current_W < W) {
        double max_MB = -1e9;
        int best_i = -1;
        
        for (int i = 0; i < n; i++) {
            if (items[i].x + eps > items[i].weight + 1e-9) continue; // Item exhausted
            
            // Calculate prefix sum S_i
            double S_i = 0;
            for (int j = 0; j <= i; j++) S_i += items[j].x;
            
            // Calculate sum of future decay impacts
            double sum_future = 0;
            for (int k = i + 1; k < n; k++) sum_future += items[k].decay * items[k].x;
            
            // Marginal Benefit Equation
            double mb = items[i].base_density - (items[i].decay * S_i) - sum_future;
            
            if (mb > max_MB) {
                max_MB = mb;
                best_i = i;
            }
        }
        
        // Stop if knapsack full or no item provides positive marginal value
        if (best_i == -1 || max_MB <= 0) break; 
        
        items[best_i].x += eps;
        current_W += eps;
    }
    
    // 3. Output results and integrate total exact value
    double total_value = 0;
    double accumulated_weight = 0;
    
    printf("Optimal Fractional Choices & Schedule:\n");
    for (int i = 0; i < n; i++) {
        if (items[i].x > 0) {
            printf("Item %d: Take %.4f units\n", items[i].id, items[i].x);
            // Integral of (density - decay * t) dt from accumulated_weight to accumulated_weight + x
            double val = (items[i].base_density * items[i].x) 
                       - (items[i].decay * items[i].x * accumulated_weight) 
                       - (0.5 * items[i].decay * items[i].x * items[i].x);
            total_value += val;
            accumulated_weight += items[i].x;
        }
    }
    printf("Total Maximized Value: %.4f\n", total_value);
    
    return 0;
}
