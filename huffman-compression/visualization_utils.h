#ifndef VISUALIZATION_UTILS_H
#define VISUALIZATION_UTILS_H

#include <stddef.h> // for size_t
#include "structures.h"

void visualize_file(char *mapped_file, size_t file_size, freq_pair *freq, int freq_size);

#endif // VISUALIZATION_UTILS_H