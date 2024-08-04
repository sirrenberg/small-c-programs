#ifndef MMAP_UTILS_H
#define MMAP_UTILS_H

#include <stddef.h> // for size_t

// Function declarations
char *map_file(const char *filename, size_t *file_size);
void unmap_file(const char *mapped_file, size_t *file_size);

#endif // MMAP_UTILS_H
