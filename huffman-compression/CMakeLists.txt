cmake_minimum_required(VERSION 3.10)
project(HuffmanEncoding C)

# Set the C standard
set(CMAKE_C_STANDARD 99)

# Specify the build type as Debug
set(CMAKE_BUILD_TYPE Debug)

# Add the executable
add_executable(HuffmanEncoding huffman.c mmap_utils.c visualization_utils.c)
