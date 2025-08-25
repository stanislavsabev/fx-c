#ifndef __FX_H__
#define __FX_H__
#include <stddef.h>   // for NULL
#include <stdint.h>
#include <stdlib.h>   // for malloc
#include <string.h>   // for memset

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
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
typedef uintptr_t up64;
typedef intptr_t p64;
typedef size_t usize;
typedef ptrdiff_t i64;

#define enum8(type)  u8
#define enum16(type) u16
#define enum32(type) u32
#define enum64(type) u64

#define NULL  ((void *)0)
#define true  1
#define false 0

#ifndef MEM_DEFAULT_ALIGNMENT
#define MEM_DEFAULT_ALIGNMENT (2 * sizeof(void *))
#endif

#ifndef offsetof
#ifdef __GNUC__
#define offsetof(type, member) __builtin_offsetof(type, member)
#else
#define offsetof(type, member) ((size_t)&((type *)0)->member)
#endif
#endif

#if defined(__cplusplus)
#define alignof(type) alignof(type)
#elif defined(__GNUC__) || defined(__clang__)
#define alignof(type) __alignof__(type)
#elif defined(_MSC_VER)
#define alignof(type) __alignof(type)
#else
#define alignof(type)    \
    offsetof(            \
        struct {         \
            char c;      \
            type member; \
        },               \
        member)
#endif

#define mem_zero(ptr, size) memset((ptr), 0, (size))

typedef struct String {
    u8 *data;
    u64 len;
} String;

typedef struct Arena {
    u8 *data;
    u64 capacity;
    u64 offset;
} Arena;

typedef struct ArenaSnapshot {
    Arena *arena;
    u64 offset;        // The offset at the time of the snapshot
} ArenaSnapshot;

#define fn
fn b8 mem_is_power_of_two(u64 value);
fn u64 mem_align_forward(u64 value, u64 alignment);
fn void arena_init(Arena *arena, void *buffer, u64 capacity);

fn void *arena_alloc_align(Arena *arena, u64 size, u64 alignment, b32 set_zero);
#define arena_alloc(arena, size)        arena_alloc_align(arena, size, MEM_DEFAULT_ALIGNMENT, true)
#define arena_alloc_struct(arena, type) arena_alloc_align(arena, sizeof(type), alignof(type), true)
#define arena_alloc_array(arena, count, type) \
    arena_alloc_align(arena, (count) * sizeof(type), alignof(type[1]))

fn void arena_free(Arena *arena);
fn void arena_reset(Arena *arena);
#endif   // __FX_H__

#ifdef FX_IMPLEMENTATION

#endif   // FX_IMPLEMENTATION
