#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to hold character and its remaining frequency
typedef struct {
    char c;
    int freq;
} Node;

// --------------------------------------------------------
// Max-Heap Implementation (1-based indexing)
// --------------------------------------------------------
void push_heap(Node* heap, int* size, Node val) {
    int i = ++(*size);
    while (i > 1 && heap[i / 2].freq < val.freq) {
        heap[i] = heap[i / 2];
        i /= 2;
    }
    heap[i] = val;
}

Node pop_heap(Node* heap, int* size) {
    Node max_val = heap[1];
    Node temp = heap[(*size)--];
    int i = 1, child = 2;
    
    while (child <= *size) {
        if (child < *size && heap[child + 1].freq > heap[child].freq) {
            child++;
        }
        if (temp.freq >= heap[child].freq) break;
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
char* rearrange_string(char* S, int K) {
    int len = strlen(S);
    if (K <= 1) return strdup(S);
    
    // 1. Count character frequencies
    int freq[256] = {0};
    for (int i = 0; i < len; i++) {
        freq[(unsigned char)S[i]]++;
    }
    
    // 2. Initialize Max-Heap
    Node heap[257]; // Max 256 unique ASCII characters + 1 for 1-based index
    int heap_size = 0;
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            Node n = {(char)i, freq[i]};
            push_heap(heap, &heap_size, n);
        }
    }
    
    // 3. Initialize Cooldown Queue and Result String
    Node* cooldown_queue = (Node*)calloc(K, sizeof(Node));
    char* result = (char*)malloc((len + 1) * sizeof(char));
    
    for (int i = 0; i < len; i++) {
        // Release character from cooldown if its distance constraint is met
        int queue_idx = i % K;
        if (cooldown_queue[queue_idx].freq > 0) {
            push_heap(heap, &heap_size, cooldown_queue[queue_idx]);
        }
        
        // If heap is empty but we still need characters, it's impossible
        if (heap_size == 0) {
            free(cooldown_queue);
            free(result);
            return strdup("");
        }
        
        // Greedily take the most frequent character
        Node current = pop_heap(heap, &heap_size);
        result[i] = current.c;
        current.freq--;
        
        // Place the used character into the cooldown queue
        cooldown_queue[queue_idx] = current;
    }
    
    result[len] = '\0';
    free(cooldown_queue);
    return result;
}

int main() {
    char str1[] = "aabbcc";
    int k1 = 3;
    printf("Input: \"%s\", K=%d\nOutput: \"%s\"\n\n", str1, k1, rearrange_string(str1, k1));
    // Expected Output: "abcabc"

    char str2[] = "aaabc";
    int k2 = 3;
    printf("Input: \"%s\", K=%d\nOutput: \"%s\"\n\n", str2, k2, rearrange_string(str2, k2));
    // Expected Output: "" (Impossible to separate 'a' by 3 positions)

    char str3[] = "aaadbbcc";
    int k3 = 2;
    printf("Input: \"%s\", K=%d\nOutput: \"%s\"\n", str3, k3, rearrange_string(str3, k3));
    // Expected Output: "abacabcd" (or similar valid permutation)

    return 0;
}