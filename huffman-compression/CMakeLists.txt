cmake_minimum_required(VERSION 3.10)
project(HuffmanEncoding C)

# Set the C standard
set(CMAKE_C_STANDARD 99)

# Specify the build type as Debug
set(CMAKE_BUILD_TYPE Debug)

# Add the include directory for the public headers
include_directories(${PROJECT_SOURCE_DIR}/include)

# Add the library target
add_library(HuffmanLib src/structures.c src/mmap_utils.c src/visualization_utils.c)

# Add the executable and link it with the library
add_executable(HuffmanEncoding src/huffman.c)
target_link_libraries(HuffmanEncoding HuffmanLib)