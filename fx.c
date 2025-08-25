#include "fx.h"


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
    a->data = (u8 *)buffer;
    a->capacity = capacity;
    a->offset = 0;
}

fn void *arena_alloc_align(Arena *arena, u64 size, u64 alignment, b32 set_zero) {
    up64 curr_ptr = (up64)(arena->data + arena->offset);
    up64 offset = mem_align_forward(curr_ptr, alignment);
    offset -= (up64)arena->data;   // Adjust offset to be relative to arena->data

    if (offset + size > arena->capacity) {
        return NULL;   // Not enough space in the arena
    }

    void *ptr = &arena->data[offset];
    arena->offset = offset + size;

    if (set_zero) {
        mem_zero(ptr, size);
    }
    return ptr;
}

fn void arena_free(Arena *arena) {
    // No-op, as we don't manage heap memory in the arena
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
