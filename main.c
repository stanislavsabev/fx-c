#define FX_IMPLEMENTATION
#include "fx.h"
#include <stdio.h>
#include <assert.h>


int main() {

    u32 ARENA_CAPACITY = 256;
    s8 buffer[ARENA_CAPACITY];
    Arena a = {0};
    arena_init(&a, buffer, ARENA_CAPACITY);

    i32 *ints = (i32*)arena_alloc(&a, sizeof(i32) * 100);
    i32 *p = ints;

    for(usize x = 0; x < 100; ++x){
        i32 v = *p++;
        v *= 2;
        printf("v=%d", v);
    }
    return 0;
}