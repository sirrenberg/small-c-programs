#ifndef VISUALIZATION_UTILS_H
#define VISUALIZATION_UTILS_H

#include <stddef.h> // for size_t

void visualize_file(char *mapped_file, size_t file_size, long long *freq, int freq_size);

#endif // VISUALIZATION_UTILS_H