#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "structures.h"

// build test with gcc -g -Iinclude src/structures.test.c src/structures.c -o build-test/structures.test

int int_cmp(const void *a, const void *b){
    return *(const int *) a - *(const int *) b;
}

void test_pop_heap(){
    int arr[6] = {9,2,17,3,5,1};
    int sorted_arr[6] = {1,2,3,5,9,17};
    size_t heap_size = 6;
    make_heap(arr, heap_size, sizeof(int), int_cmp);
    for(int i = heap_size; i > 0 ; --i){
         pop_heap(arr, i, sizeof(int), int_cmp);
         assert(arr[i-1] == sorted_arr[i-1]);
    }
}

void test_push_heap(){
    // Setup
    int arr[20] = {9,2,17,3,5,1};
    int cmp_arr[20];
    size_t heap_size = 6;
    make_heap(arr, heap_size, sizeof(int), int_cmp);
    int values_to_insert[10] = {93, 12, 155, 63, 4, 9, 7, 75, 3, 85};

    // insert values and check that make_heap does not change the array, after the heap condition was restored with push_heap
    for(int i = 0; i < 10; ++i){
        arr[heap_size] = values_to_insert[i];
        push_heap(arr, heap_size, sizeof(int), int_cmp);
        ++heap_size;

        memcpy(cmp_arr, arr, heap_size * sizeof(int));
        make_heap(arr, heap_size, sizeof(int), int_cmp);

        for(int j = 0; j < heap_size; ++j){
            assert(arr[j] == cmp_arr[j]);
            printf("%d, ", arr[j]);
        }
        printf("\n");
    }

    int current_heap_size = heap_size;
    for(int i = 0; i < current_heap_size; ++i){
        pop_heap(arr, heap_size, sizeof(int), int_cmp);
        --heap_size;
        printf("%d, ", arr[heap_size]);
    }
}

int main(){
    test_pop_heap();
    test_push_heap();
    return 0;
}