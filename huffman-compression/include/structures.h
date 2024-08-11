#ifndef STRUCTURES_H
#define STRUCTURES_H

typedef struct {
    long long freq;
    char c;
} FreqPair;


/**
 * Comparison function used for the heap.
 */
typedef int (*compare_func)(const void *, const void *);

/**
 * Makes a heap out of an array.
 */
void make_heap(void *arr, size_t arr_size, size_t elem_size, compare_func cmp);

/**
 * Swaps the first element of the heap with the last element and restores the heap property.
 * Afterwards, the heap is of size arr_size - 1, and the popped element can be read at index arr_size - 1.
 */
void pop_heap(void *arr, size_t arr_size, size_t elem_size, compare_func cmp);

#endif // STRUCTURES_H