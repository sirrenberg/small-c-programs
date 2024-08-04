#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "mmap_utils.h"
#include "visualization_utils.h"

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

    long long freq[256] = { 0 }; // use a hashmap to keep track of the frequency of each byte. Hash function: Identity. Works well because we know the value to be bounded.
    int freq_size = 256;

    for (size_t i = 0; i < file_size; ++i){
        freq[mapped_file[i]] += 1;
    }

    visualize_file(mapped_file, file_size, freq, freq_size); // write the content of the file to stdout in a nice way.

    // TODO: create binary tree in array to keep locality and avoid pointer chasing

    typedef struct {
        char value;
        struct huffman_tree *left;
        struct huffman_tree *right;
    } huffman_tree;

    // Unmap the file
    unmap_file(mapped_file, file_size);
    return EXIT_SUCCESS;
}
