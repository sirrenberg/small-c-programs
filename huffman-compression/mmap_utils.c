#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

// Function to map a file into memory
char *map_file(const char *filename, size_t *file_size) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("Failed to open file");
        return NULL;
    }

    // Get the size of the file
    struct stat st;
    if (fstat(fd, &st) == -1) {
        perror("Failed to get file size");
        close(fd);
        return NULL;
    }
    *file_size = st.st_size;

    // Map the file into memory
    char *mapped_file = mmap(NULL, *file_size, PROT_READ, MAP_PRIVATE, fd, 0);
    if (mapped_file == MAP_FAILED) {
        perror("Failed to mmap file");
        close(fd);
        return NULL;
    }

    close(fd);
    return mapped_file;
}

// Function to unmap the file
void unmap_file(char *mapped_file, size_t *file_size) {
    if (munmap(mapped_file, *file_size) == -1) {
        perror("Failed to munmap file");
    }
}
