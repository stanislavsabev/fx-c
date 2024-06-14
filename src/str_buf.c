#include <assert.h>
#include <string.h>

#include "strlib.h"
#include "util.h"

#define _FXSTR_GROW_MULTIPLIER  2
#define _FXSTR_INITIAL_CAPACITY 8

/**
 * @brief For internal use. Computes the capacity of the next grow.
 * Capacity is increased by multiples of 2.
 * @param capacity_ current capacity
 * @return size_t - capacity after next grow
 */
static inline size_t _str_compute_next_grow(size_t capacity_) {
    return capacity_ ? capacity_ * _FXSTR_GROW_MULTIPLIER : _FXSTR_INITIAL_CAPACITY;
}

/**
 * @brief For internal use. Grows the str data.
 * @param str_p__ pointer to the str
 * @return void
 */
void _str_grow(str_buf_t* str_p__, size_t capacity_) {
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

extern inline str_buf_t fxstr_buf_create(const char* cch_p, size_t len) {
    return fxstr_buf_from_chars(cch_p, len);
}

str_buf_t fxstr_buf_acquire(char** ch_pp, size_t len) {
    str_buf_t s__ = fxstr_buf_null();
    if (len == 0 || *ch_pp == NULL) {
        return s__;
    }
    s__.data = *ch_pp;
    s__.len = len;
    s__.capacity = len;
    return s__;
}

extern inline str_buf_t fxstr_buf_from_chars(const char* chars, size_t len) {
    str_buf_t s__ = fxstr_buf_null();
    if (len == 0 || chars == NULL) {
        return s__;
    }
    _str_grow(&s__, len);
    memcpy(s__.data, chars, len);
    s__.len = len;
    return s__;
}

extern inline str_buf_t fxstr_buf_from_cstr(const char cstr[static 1]) {
    return fxstr_buf_from_chars(cstr, strlen(cstr));
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

const char* fxstr_buf_to_cstr(str_buf_t* str_p) {
    if (fxstr_buf_is_null(str_p)) {
        return NULL;
    }
    if (str_p->capacity < str_p->len + 1) {
        _str_grow(str_p, str_p->len + 1);
    }
    str_p->data[str_p->len] = '\0';
    return (const char*)str_p->data;
}

str fxstr_buf_to_str_view(const str_buf_t* str_p) {
    return (str){.data = str_p->data, .len = str_p->len};
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
        _str_grow(str_p, capacity);
    }
}

str_buf_t fxstr_buf_lsplit_buf(str_buf_t* str_p, const str_buf_t* delim) {
    const str delim_view = fxstr_view_from_chars(delim->data, delim->len);
    return fxstr_buf_lsplit_view(str_p, &delim_view);
}
str_buf_t fxstr_buf_lsplit_view(str_buf_t* str_p, const str* delim) {
    char* substr = (char*)fx_memmem(str_p->data, str_p->len, delim->data, delim->len);
    if (substr == NULL) {
        return fxstr_buf_null();
    }
    size_t left_len = substr - str_p->data;
    str_buf_t left = fxstr_buf_from_chars(str_p->data, left_len);
    size_t right_len = str_p->len - left_len - delim->len;
    str_buf_t right = fxstr_buf_from_chars(substr + delim->len, right_len);
    fxstr_buf_free(str_p);
    *str_p = right;
    return left;
}
str_buf_t fxstr_buf_lsplit_cstr(str_buf_t* str_p, const char* delim) {
    str delim_view = fxstr_view_from_cstr(delim);
    return fxstr_buf_lsplit_view(str_p, &delim_view);
}

str_buf_t fxstr_buf_lsplit_chr(str_buf_t* str_p, const char cch_delim) {
    const str delim_view = fxstr_view_from_chars(&cch_delim, 1);
    return fxstr_buf_lsplit_view(str_p, &delim_view);
}
