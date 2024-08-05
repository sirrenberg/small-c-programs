#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "mmap_utils.h"
#include "visualization_utils.h"
#include "structures.h"

int compare_freq(const void *a, const void *b) {
    freq_pair *fa = (freq_pair *)a;
    freq_pair *fb = (freq_pair *)b;
    return fb->freq - fa->freq; // Descending order, three way comparison.
}

typedef struct huffman_tree{
    char value;
    struct huffman_tree *left;
    struct huffman_tree *right;
} huffman_tree;

void free_huffman_tree(huffman_tree *node) {
    if (node == NULL) {
        return;
    }
    
    // Recursively free the left and right subtrees
    free_huffman_tree(node->left);
    free_huffman_tree(node->right);
    
    // Free the current node
    free(node);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *filename = argv[1];
    size_t file_size;

    // Map the file that should be compressed into the memory
    char *mapped_file = map_file(filename, &file_size);

    if (mapped_file == NULL) {
        return EXIT_FAILURE;
    }

    freq_pair freq[256] = {{0,0}}; // use a hashmap to keep track of the frequency of each byte. Hash function: Identity. Works well because we know the value to be bounded.
    int freq_size = 256;

    for (size_t i = 0; i < file_size; ++i){
        freq[mapped_file[i]].freq += 1;
        freq[mapped_file[i]].c = (char) mapped_file[i];
    }

    qsort(freq, freq_size, sizeof(freq_pair), compare_freq);

    for(int i = 0; i < freq_size; ++i){
        if (freq[i].freq == 0){
            freq_size = i;
            break;
        }
    }

    visualize_file(mapped_file, file_size, freq, freq_size);

    // TODO: create binary tree in array to keep locality and avoid pointer chasing



    // huffman_tree *ht0 = (huffman_tree *)malloc(sizeof(huffman_tree));
    // *ht0 = (huffman_tree) {.value = 'B', .left = NULL, .right = NULL};

    // huffman_tree *ht1 = (huffman_tree *)malloc(sizeof(huffman_tree));
    // *ht1 = (huffman_tree) {.value = 'C', .left = NULL, .right = NULL};

    // huffman_tree *ht2 = (huffman_tree *)malloc(sizeof(huffman_tree));
    // *ht2 = (huffman_tree) {.value = 'A', .left = ht0, .right = ht1};

    // free(ht0);
    // free(ht1);
    // free(ht2);

    huffman_tree *leaf_right = (huffman_tree *)malloc(sizeof(huffman_tree));
    *leaf_right = (huffman_tree) {.value = freq[freq_size - 1].c, .left = NULL, .right = NULL};

    huffman_tree *leaf_left = (huffman_tree *)malloc(sizeof(huffman_tree));
    *leaf_left = (huffman_tree) {.value = freq[freq_size - 2].c, .left = NULL, .right = NULL};

    huffman_tree *ht = (huffman_tree *)malloc(sizeof(huffman_tree));
    *ht = (huffman_tree) {.value = '0', .left = leaf_left, .right = leaf_right}; // the value inside the ht is not important.

    long long f = freq[freq_size - 1].freq + freq[freq_size - 2].freq;

    freq_size -= 2;
    for(int i = freq_size - 1; i >= 0; --i){
        printf("\n%lld",f);
        huffman_tree *inner = (huffman_tree *)malloc(sizeof(huffman_tree));
        huffman_tree *leaf = (huffman_tree *)malloc(sizeof(huffman_tree));
        *leaf = (huffman_tree) {.value = freq[i].c, .left = NULL, .right = NULL};
        if (freq[i].freq >= f){
            *inner = (huffman_tree) {.value = '0', .left = leaf, .right = ht};
            printf("%s","left");
        }
        else{
            *inner = (huffman_tree) {.value = '0', .left = ht, .right = leaf};
            printf("%s","right");
        }
        ht = inner;
        f += freq[i].freq;
    }

    printf("\n0x%02x\n", ht->right->value);
    printf("0x%02x\n", ht->left->left->value);
    printf("0x%02x\n", ht->left->right->left->value);
    printf("0x%02x\n", ht->left->right->right->value);

    free_huffman_tree(ht);

    // Unmap the file
    unmap_file(mapped_file, file_size);
    return EXIT_SUCCESS;
}
