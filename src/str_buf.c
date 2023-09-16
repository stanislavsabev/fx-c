#include <assert.h>
#include <string.h>

#include "str.h"

#define _FXSTR_GROW_MULTIPLIER  2
#define _FXSTR_INITIAL_CAPACITY 1

/**
 * @brief For internal use. Computes the capacity of the next grow.
 * Capacity is increased by multiples of 2.
 * @param capacity_ current capacity
 * @return size_t - capacity after next grow
 */
static inline size_t _fxstr_compute_next_grow(size_t capacity_) {
    return capacity_ ? capacity_ * _FXSTR_GROW_MULTIPLIER : _FXSTR_INITIAL_CAPACITY;
}

/**
 * @brief For internal use. Grows the str data.
 * @param str_p__ pointer to the str
 * @return void
 */
void _fxstr_grow(str_buf_t* str_p__, size_t capacity_) {
    const size_t ln__ = capacity_ * sizeof(*str_p__->data);
    if (str_p__->data) {
        void* data_p__ = fxstr_stdlib_realloc(str_p__->data, ln__);
        assert(data_p__);
        str_p__->data = data_p__;
    } else {
        char* data_p2__ = fxstr_stdlib_malloc(ln__);
        assert(data_p2__);
        str_p__->data = data_p2__;
        str_p__->len = 0;
    }
    str_p__->capacity = capacity_;
}

extern inline str_buf_t fxstr_buf_null(void) {
    return (str_buf_t){.capacity = 0, .len = 0, .data = NULL};
}

str_buf_t fxstr_buf_from_chars(size_t len, const char* chars) {
    str_buf_t s__ = fxstr_buf_null();
    if (len == 0 || chars == NULL) {
        return s__;
    }
    _fxstr_grow(&s__, len);
    memcpy(s__.data, chars, len);
    s__.len = len;
    return s__;
}

extern inline str_buf_t fxstr_buf_from_cstr(const char cstr[static 1]) {
    return fxstr_buf_from_chars(strlen(cstr), cstr);
}

char* fxstr_buf_to_cstr_copy(const str_buf_t* str_p) {
    if (fxstr_buf_is_null(str_p)) {
        return NULL;
    }
    char* cstr = fxstr_stdlib_malloc(str_p->len + 1);
    memcpy(str_p->data, cstr, str_p->len);
    cstr[str_p->len] = '\0';
    return cstr;
}

char* fxstr_buf_to_cstr_ref(str_buf_t* str_p) {
    if (fxstr_buf_is_null(str_p)) {
        return NULL;
    }
    if (str_p->capacity < str_p->len + 1) {
        _fxstr_grow(str_p, str_p->len + 1);
    }
    str_p->data[str_p->len] = '\0';
    return str_p->data;
}

str_view_t fxstr_buf_to_str_view(const str_buf_t* str_p) {
    return (str_view_t){.data = str_p->data, .len = str_p->len};
}

/**
 * @brief Free an fxstr allocated by
 * fxstr_stdlib_malloc', fxstr_stdlib_realloc' or `fxstr_stdlib_calloc'.
 * @return void
 */
void fxstr_buf_free(str_buf_t* str_p) {
    if (str_p->data) {
        fxstr_stdlib_free(str_p->data);
        str_p->data = NULL;
        str_p->len = 0;
        str_p->capacity = 0;
    }
}

/**
 * @brief Reserve an fxstr allocated by
 * @param str_p pointer to the str
 * @param str_p pointer to the str
 * fxstr_stdlib_malloc', fxstr_stdlib_realloc' or `fxstr_stdlib_calloc'.
 * @return void
 */
void fxstr_buf_reserve(str_buf_t* str_p, size_t capacity) {
    if (str_p->capacity < capacity) {
        _fxstr_grow(str_p, capacity);
    }
}
