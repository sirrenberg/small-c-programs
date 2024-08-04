#include <stddef.h> // for size_t
#include <stdio.h>
#include "structures.h"

/**
 * Print the input file as ASCII Values, as Hex Values and the count of each Byte value.
 */
void visualize_file(char *mapped_file, size_t file_size, freq_pair *freq, int freq_size){
    printf("%s", "ASCII Values: ");

    for (size_t i = 0; i < file_size; ++i) {
        putchar(mapped_file[i]);
    }

    printf("%s", "\nHex Values: ");

    for (size_t i = 0; i < file_size; ++i) {
        printf("0x%02x", mapped_file[i]);
    }

    printf("%s", "\nFrequencies of each Byte:");

    for (int i = 0; i < freq_size; ++i){
        if (!(i % 16)){
            putchar('\n');
        }
        printf("0x%02x: %2lld  ", freq[i].c, freq[i].freq);
    }
}
