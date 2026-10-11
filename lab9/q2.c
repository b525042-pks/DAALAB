#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Standard Huffman Tree Node
typedef struct Node {
    char symbol;
    int freq;
    struct Node *left, *right;
    int is_leaf;
} Node;

// Canonical Codebook Entry
typedef struct {
    char symbol;
    int length;
    unsigned int code;
} CanonicalCode;

// Helper to create a new node
Node* create_node(char symbol, int freq, Node* left, Node* right, int is_leaf) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->symbol = symbol;
    node->freq = freq;
    node->left = left;
    node->right = right;
    node->is_leaf = is_leaf;
    return node;
}

// DFS traversal to determine bit lengths of each symbol
void determine_lengths(Node* root, int depth, CanonicalCode* codes, int* index) {
    if (!root) return;
    if (root->is_leaf) {
        codes[*index].symbol = root->symbol;
        codes[*index].length = depth;
        (*index)++;
    }
    determine_lengths(root->left, depth + 1, codes, index);
    determine_lengths(root->right, depth + 1, codes, index);
}

// Sorting comparator: Primary by length (asc), Secondary by symbol (asc)
int compare_canonical(const void* a, const void* b) {
    CanonicalCode* c1 = (CanonicalCode*)a;
    CanonicalCode* c2 = (CanonicalCode*)b;
    if (c1->length != c2->length) {
        return c1->length - c2->length;
    }
    return c1->symbol - c2->symbol;
}

// Utility to print binary representation
void print_binary(unsigned int code, int length) {
    for (int i = length - 1; i >= 0; i--) {
        printf("%d", (code >> i) & 1);
    }
}

int main() {
    // 1. Input Representation: Frequencies of symbols
    char symbols[] = {'A', 'B', 'C', 'D', 'E', 'F'};
    int freqs[] = {45, 13, 12, 16, 9, 5};
    int n = sizeof(symbols) / sizeof(symbols[0]);

    // Initialize array of active tree nodes
    Node** active_nodes = (Node**)malloc(n * sizeof(Node*));
    for (int i = 0; i < n; i++) {
        active_nodes[i] = create_node(symbols[i], freqs[i], NULL, NULL, 1);
    }

    // 2. Build Huffman Tree (O(N^2) array scan for simplicity; Min-Heap used in O(N log N) theory)
    int active_count = n;
    while (active_count > 1) {
        int min1 = -1, min2 = -1;
        
        // Find two nodes with minimum frequencies
        for (int i = 0; i < active_count; i++) {
            if (min1 == -1 || active_nodes[i]->freq < active_nodes[min1]->freq) {
                min2 = min1;
                min1 = i;
            } else if (min2 == -1 || active_nodes[i]->freq < active_nodes[min2]->freq) {
                min2 = i;
            }
        }

        // Merge the two minimum nodes
        Node* merged = create_node('\0', active_nodes[min1]->freq + active_nodes[min2]->freq, 
                                   active_nodes[min1], active_nodes[min2], 0);
        
        // Replace min1 with merged node, move last active node to min2's spot
        active_nodes[min1] = merged;
        active_nodes[min2] = active_nodes[active_count - 1];
        active_count--;
    }
    Node* root = active_nodes[0];

    // 3. Extract lengths via DFS
    CanonicalCode codes[n];
    int code_index = 0;
    determine_lengths(root, 0, codes, &code_index);

    // 4. Sort to enforce Canonical order
    qsort(codes, n, sizeof(CanonicalCode), compare_canonical);

    // 5. Generate Canonical Codes mathematically
    codes[0].code = 0;
    for (int i = 1; i < n; i++) {
        codes[i].code = (codes[i - 1].code + 1) << (codes[i].length - codes[i - 1].length);
    }

    // 6. Output formatted codebook
    printf("Canonical Huffman Codebook:\n");
    printf("Sym | Len | Code\n");
    printf("------------------\n");
    for (int i = 0; i < n; i++) {
        printf(" %c  |  %d  | ", codes[i].symbol, codes[i].length);
        print_binary(codes[i].code, codes[i].length);
        printf("\n");
    }

    return 0;
}