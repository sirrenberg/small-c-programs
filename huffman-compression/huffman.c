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

    typedef struct huffman_tree{
        char value;
        struct huffman_tree *left;
        struct huffman_tree *right;
    } huffman_tree;

    huffman_tree *ht0 = (huffman_tree *)malloc(sizeof(huffman_tree));
    *ht0 = (huffman_tree) {.value = 'B', .left = NULL, .right = NULL};

    huffman_tree *ht1 = (huffman_tree *)malloc(sizeof(huffman_tree));
    *ht1 = (huffman_tree) {.value = 'C', .left = NULL, .right = NULL};

    huffman_tree *ht2 = (huffman_tree *)malloc(sizeof(huffman_tree));
    *ht2 = (huffman_tree) {.value = 'A', .left = ht0, .right = ht1};

    free(ht0);
    free(ht1);
    free(ht2);

    // Unmap the file
    unmap_file(mapped_file, file_size);
    return EXIT_SUCCESS;
}
