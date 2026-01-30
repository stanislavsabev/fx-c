#ifndef __FX_LIB__
#define __FX_LIB__
#include <stddef.h>   // for NULL
#include <stdint.h>
#include <stdlib.h>   // for malloc
#include <string.h>   // for memset
#include <stdbool.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
typedef int8_t i8;
typedef int8_t s8;
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


#ifndef MEM_DEFAULT_ALIGNMENT
#define MEM_DEFAULT_ALIGNMENT (2 * sizeof(void *))
#endif

#define alignof(type) __alignof__(type)

#define mem_zero(ptr, size) memset((ptr), 0, (size))

typedef struct String {
    u8 *data;
    u64 len;
} String;

typedef struct Arena {
    u8 *buffer;
    u64 buffer_size;
    u64 offset;
} Arena;

typedef struct ArenaSnapshot {
    Arena *arena;
    u64 offset;        // The offset at the time of the snapshot
} ArenaSnapshot;

#define fn

b8 mem_is_power_of_two(u64 value);
u64 mem_align_forward(u64 ptr, u64 alignment);
void arena_init(Arena *a, void *buffer, u64 capacity);
void *arena_alloc_align(Arena *arena, u64 size, u64 alignment, b32 set_zero);
void arena_free(Arena *arena);
void arena_reset(Arena *arena);
ArenaSnapshot arena_snapshot_save(Arena *arena);
void arena_snapshot_restore(ArenaSnapshot snapshot);

#ifdef FX_IMPLEMENTATION


fn b8 mem_is_power_of_two(u64 value) {
    return (value & (value - 1)) == 0;
}

#include <assert.h>


fn u64 mem_align_forward(u64 ptr, u64 alignment) {
    assert(mem_is_power_of_two(alignment) && "Alignment must be a power of two");

    u64 p, a, modulo;
    p = ptr;
    a = alignment;
    modulo = p % (a - 1); 
    if (modulo != 0) {
        p += a - modulo;
    }
    return p;
}

fn void arena_init(Arena *a, void *buffer, u64 capacity) {
    a->buffer = (u8 *)buffer;
    a->buffer_size = capacity;
    a->offset = 0;
}

fn void *arena_alloc_align(Arena *arena, u64 size, u64 alignment, b32 set_zero) {
    up64 curr_ptr = (up64)(arena->buffer + arena->offset);
    up64 offset = mem_align_forward(curr_ptr, alignment);
    offset -= (up64)arena->buffer;   // Adjust offset to be relative to arena->data

    if (offset + size > arena->buffer_size) {
        return NULL;   // Not enough space in the arena
    }

    void *ptr = &arena->buffer[offset];
    arena->offset = offset + size;

    if (set_zero) {
        mem_zero(ptr, size);
    }
    return ptr;
}

fn void *arena_alloc(Arena *arena, u64 size) {
    return arena_alloc_align(arena, size, MEM_DEFAULT_ALIGNMENT, true);
}

fn void arena_free(Arena *arena) {
    // No-op, as we don't manage heap memory in the arena
    (void)arena;
}

// Get remaining space in arena
size_t arena_remaining(Arena* arena) {
    return arena->buffer_size - arena->offset;
}
fn void arena_reset(Arena *arena) {
    arena->offset = 0;
}

fn ArenaSnapshot arena_snapshot_save(Arena *arena) {
    ArenaSnapshot snapshot;
    snapshot.arena = arena;
    snapshot.offset = arena->offset;
    return snapshot;
}

fn void arena_snapshot_restore(ArenaSnapshot snapshot) {
    Arena *arena = snapshot.arena;
    arena->offset = snapshot.offset;
}


#endif   // FX_IMPLEMENTATION
#endif   // __FX_LIB__
