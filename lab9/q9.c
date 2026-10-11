#include <stdio.h>
#include <stdlib.h>

// --------------------------------------------------------
// Tree Node Definition
// --------------------------------------------------------
typedef struct Node {
    int id;          // Original sequence index, -1 for internal nodes
    int weight;      // Weight/frequency of the node
    int is_leaf;     // 1 if leaf, 0 if internal
    struct Node* left;
    struct Node* right;
} Node;

Node* create_node(int id, int weight, int is_leaf, Node* left, Node* right) {
    Node* n = (Node*)malloc(sizeof(Node));
    n->id = id;
    n->weight = weight;
    n->is_leaf = is_leaf;
    n->left = left;
    n->right = right;
    return n;
}

// --------------------------------------------------------
// DFS to Calculate Final Minimum Cost
// --------------------------------------------------------
int calculate_optimal_cost(Node* root, int depth) {
    if (!root) return 0;
    // If it's a leaf, cost is weight * depth
    if (root->is_leaf) {
        printf("Leaf %d (Weight %d) ends up at Depth %d\n", root->id, root->weight, depth);
        return root->weight * depth;
    }
    // Traverse children
    return calculate_optimal_cost(root->left, depth + 1) + 
           calculate_optimal_cost(root->right, depth + 1);
}

// --------------------------------------------------------
// Hu-Tucker Phase 1 Simulation
// --------------------------------------------------------
int optimal_alphabetic_cost(int* weights, int n) {
    if (n == 0) return 0;
    if (n == 1) return 0; // Depth is 0 for a single root

    Node** active_nodes = (Node**)malloc(n * sizeof(Node*));
    for (int i = 0; i < n; i++) {
        active_nodes[i] = create_node(i + 1, weights[i], 1, NULL, NULL);
    }

    int active_count = n;

    // Phase 1: N-1 Merges
    for (int step = 0; step < n - 1; step++) {
        int best_i = -1, best_j = -1;
        int min_sum = 1000000000; // Infinity placeholder

        for (int i = 0; i < active_count - 1; i++) {
            for (int j = i + 1; j < active_count; j++) {
                // Check compatibility: No leaves between i and j
                int compatible = 1;
                for (int m = i + 1; m < j; m++) {
                    if (active_nodes[m]->is_leaf) {
                        compatible = 0;
                        break; 
                    }
                }
                
                // If a leaf is in between, all subsequent j's are also incompatible with i
                if (!compatible) break;

                int current_sum = active_nodes[i]->weight + active_nodes[j]->weight;
                if (current_sum < min_sum) {
                    min_sum = current_sum;
                    best_i = i;
                    best_j = j;
                }
            }
        }

        // Merge the best compatible pair
        Node* merged = create_node(-1, min_sum, 0, active_nodes[best_i], active_nodes[best_j]);
        
        // Place new node at the leftmost position (best_i)
        active_nodes[best_i] = merged;

        // Shift remaining nodes left to close the gap at best_j
        for (int m = best_j; m < active_count - 1; m++) {
            active_nodes[m] = active_nodes[m + 1];
        }
        active_count--;
    }

    // The remaining node is the root of the Phase 1 tree
    Node* root = active_nodes[0];
    int total_cost = calculate_optimal_cost(root, 0);

    free(active_nodes);
    return total_cost;
}

int main() {
    // Example test case
    int weights[] = {2, 3, 1, 4};
    int n = sizeof(weights) / sizeof(weights[0]);
    
    printf("Input Weights: [");
    for (int i=0; i<n; i++) printf("%d%s", weights[i], i==n-1 ? "" : ", ");
    printf("]\n\n");
    
    int min_cost = optimal_alphabetic_cost(weights, n);
    printf("\nTotal Minimum Cost: %d\n", min_cost);

    return 0;
}