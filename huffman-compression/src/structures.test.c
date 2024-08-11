#include <stddef.h>
#include <stdio.h>
#include <assert.h>
#include "structures.h"

// build test with gcc -Iinclude src/structures.test.c src/structures.c -o build-test/structures.test

int int_cmp(const void *a, const void *b){
    int ia = *(const int *) a;
    int ib = *(const int *) b;
    return ia - ib;
}

void test_heap(){
    int arr[6] = {9,2,17,3,5,1};
    int sorted_arr[6] = {1,2,3,5,9,17};
    size_t heap_size = 6;
    make_heap(arr, heap_size, sizeof(int), int_cmp);
    for(int i = heap_size; i > 0 ; --i){
         pop_heap(arr, i, sizeof(int), int_cmp);
         assert(arr[i-1] == sorted_arr[i-1]);
    }
}

int main(){
    test_heap();
    return 0;
}