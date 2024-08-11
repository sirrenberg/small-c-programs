#include <stddef.h>
#include <string.h>
#include "structures.h"

typedef int (*compare_func)(const void *, const void *);

static inline void swap(void *arr, size_t i1, size_t i2, size_t elem_size){
    char tmp[elem_size];
        memcpy(tmp, (char *)arr + i1 * elem_size, elem_size);
        memcpy((char *)arr + i1 * elem_size, (char *)arr + i2 * elem_size, elem_size);
        memcpy((char *)arr + i2 * elem_size, tmp, elem_size);
}

/**
 * Heapify function that can be used with min-heaps and max-heaps. Just the comparison function has to be adjusted.
 * @param i Index of the root element of the subtree that should be heapified.
 */
void heapify(void *arr, size_t arr_size, size_t i, size_t elem_size, compare_func cmp) {
    size_t largest = i;
    size_t left = 2 * i + 1; // left child node
    size_t right = 2 * i + 2; // right child node

    if (left < arr_size && cmp((char *)arr + left * elem_size, (char *)arr + largest * elem_size) > 0) {
        largest = left;
    }

    if (right < arr_size && cmp((char *)arr + right * elem_size, (char *)arr + largest * elem_size) > 0) {
        largest = right;
    }

    if (largest != i) {
        // Swap elements
        swap(arr, i, largest, elem_size);

        // int *int_arr = (int *) arr;
        // for(int i = 0; i < arr_size; ++i){
        //     printf("%d, ", int_arr[i]);
        // }
        
        // Recursively heapify the affected sub-tree
        heapify(arr, arr_size, largest, elem_size, cmp);
    }
}

void make_heap(void *arr, size_t arr_size, size_t elem_size, compare_func cmp) {
    size_t first_leaf_node = arr_size / 2; // all leaf nodes, i.e. heaps of size 1 are per definition always a heap, don't need to be heapified.
    for (size_t i = first_leaf_node; i > 0; --i) {
        heapify(arr, arr_size, i - 1, elem_size, cmp);
    }
}

void pop_heap(void *arr, size_t arr_size, size_t elem_size, compare_func cmp){
    swap(arr, 0, arr_size - 1, elem_size);
    heapify(arr, arr_size - 1 , 0 , elem_size, cmp);
}