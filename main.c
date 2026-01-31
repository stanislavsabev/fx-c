#define FX_IMPLEMENTATION
#include <assert.h>
#include <stdio.h>

#include "fx.h"

typedef struct ByteArray {
    usize len;
    char* data;
} ByteArray;

int main() {
    u32 ARENA_CAPACITY = 256;
    i8 buffer[ARENA_CAPACITY];
    Arena a = {0};
    arena_init(&a, buffer, ARENA_CAPACITY);

    usize len = 100;

    // char *chars = (char *)arena_alloc(&a, sizeof(char) * len);
    ByteArray* barr = (ByteArray*)arena_alloc(&a, sizeof(ByteArray) + sizeof(char) * len);
    barr->data = (char*)arena_alloc(&a, sizeof(char) + sizeof(char) * len);

    barr->len = len;
    memset(barr->data, 'a', barr->len);

    for (usize x = 0; x < barr->len; ++x) {
        char p = barr->data[x];
        char* py = barr->data + x;
        printf("%c:%c ", p, *py);
    }

    // for(usize x = 0; x < len; ++x){
    //     char v = *(chars + x);
    //     printf("%c ", v);
    // }
    printf("\n");

    memset(barr->data, 'b', barr->len);
    // memset(chars, 'b', len);

    for (usize x = 0; x < barr->len; ++x) {
        char y = barr->data[x];
        printf("%c ", y);
    }
    // for(usize x = 0; x < len; ++x){
    //     char v = *(chars + x);
    //     printf("%c ", v);
    // }
    printf("\n");

    return 0;
}