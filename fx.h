#ifndef __FX_H__
#define __FX_H__
#include <stdint.h>
#include <stdlib.h>  // for malloc
#include <string.h>  // for memset
#include <stddef.h>  // for NULL

typedef uint8_t u8;
typedef uint8_t u16;
typedef uint8_t u32;
typedef uint8_t u64;
typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef float f32;
typedef double f64;
typedef int8_t b8;
typedef int16_t b16;
typedef int32_t b32;
typedef int64_t b64;
typedef wchar_t wchar;
typedef uintptr_t u64;
typedef intptr_t i64;
typedef size_t u64;
typedef ptrdiff_t i64;

#define enum8(type) u8
#define enum16(type) u16
#define enum32(type) u32
#define enum64(type) u64

#define NULL ((void *)0)
#define TRUE 1
#define FALSE 0

#ifndef MEM_DEFAULT_ALIGNMENT
#define MEM_DEFAULT_ALIGNMENT (2*sizeof(void *))
#endif

# define mem_zero(ptr, size) memset((ptr), 0, (size))

typedef struct Buffer {
    u64 size;
    u8 *data;
} Buffer;

typedef struct String {
    u64 len;
    u8 *data;
} String;

typedef struct Arena {
    u64 capacity;
    u64 offset;
    u64 prev_offset;
    u8 *data;
} Arena;

#define fn
b8 mem_is_power_of_two(u64 value);
u64 mem_align_forward(u64 value, u64 alignment);

#endif // __FX_H__

#ifndef FX_IMPLEMENTATION

b8 mem_is_power_of_two(u64 value) {
    return (value & (value - 1)) == 0;
}

u64 mem_align_forward(u64 value, u64 alignment) {
    if (alignment == 0) return value;
    return (value + alignment - 1) & ~(alignment - 1);
}

#endif // FX_IMPLEMENTATION
