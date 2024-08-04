cmake_minimum_required(VERSION 3.10)
project(HuffmanEncoding C)

set(CMAKE_C_STANDARD 99)

# Add the executable
add_executable(HuffmanEncoding huffman.c mmap_utils.c)
