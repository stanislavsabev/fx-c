/*
String implementation
*/

#include "strlib.h"

#include <assert.h>
#include <string.h>

#include "util.h"

#define _FX_GROW_MULTIPLIER  2
#define _FX_INITIAL_CAPACITY 8

/* str */

extern inline str fx_str_null(void) {
    return fx_str_from_chars(NULL, 0);
}

extern inline str fx_str_create(const char* data, size_t len) {
    return fx_str_from_chars(data, len);
}

extern inline str fx_str_from_chars(const char* chars, size_t len) {
    return (str){.len = len, .data = chars};
}

extern inline str fx_str_from_cstr(const char cstr[static 1]) {
    return fx_str_from_chars(cstr, strlen(cstr));
}

char* fx_str_to_cstr(const str* str_p) {
    char* cstr = fx_stdlib_malloc(str_p->len + 1);
    memcpy(cstr, str_p->data, str_p->len);
    cstr[str_p->len] = '\0';
    return cstr;
}

str fx_str_lsplit_by_str(str* str_p, const str* delim) {
    char* substr = (char*)fx_memmem(str_p->data, str_p->len, delim->data, delim->len);
    if (substr == NULL) {
        return fx_str_null();
    }
    size_t left_len = substr - str_p->data;
    str left = fx_str_null();
    if (left_len > 0) {
        left = fx_str_from_chars(str_p->data, left_len);
    }
    str_p->len -= left_len + delim->len;
    if (str_p->len == 0) {
        str_p->data = NULL;
    } else {
        str_p->data = substr + delim->len;
    }
    return left;
}

str fx_str_lsplit_by_String(str* str_p, const String* delim) {
    const str delim_view = fx_str_from_chars(delim->data, delim->len);
    return fx_str_lsplit_by_str(str_p, &delim_view);
}

str fx_str_lsplit_by_cstr(str* str_p, const char* delim) {
    const str delim_view = fx_str_from_cstr(delim);
    return fx_str_lsplit_by_str(str_p, &delim_view);
}

str fx_str_lsplit_by_chr(str* str_p, const char cch_delim) {
    const str delim_view = fx_str_from_chars(&cch_delim, 1);
    return fx_str_lsplit_by_str(str_p, &delim_view);
}

/* String */

/**
 * @brief For internal use. Computes the capacity of the next grow.
 * Capacity is increased by multiples of 2.
 * @param capacity_ current capacity
 * @return size_t - capacity after next grow
 */
static inline size_t _str_compute_next_grow(size_t capacity_) {
    return capacity_ ? capacity_ * _FX_GROW_MULTIPLIER : _FX_INITIAL_CAPACITY;
}

/**
 * @brief For internal use. Grows the str data.
 * @param str_p__ pointer to the str
 * @return void
 */
void _str_grow(String* str_p__, size_t capacity_) {
    const size_t ln__ = capacity_ * sizeof(*str_p__->data);
    if (str_p__->data) {
        void* data_p__ = fx_stdlib_realloc(str_p__->data, ln__);
        assert(data_p__);
        str_p__->data = data_p__;
    } else {
        char* data_p2__ = fx_stdlib_malloc(ln__);
        assert(data_p2__);
        str_p__->data = data_p2__;
        str_p__->len = 0;
    }
    str_p__->capacity = capacity_;
}

extern inline String fx_String_null(void) {
    return (String){.capacity = 0, .len = 0, .data = NULL};
}

extern inline String fx_String_create(const char* cch_p, size_t len) {
    return fx_String_from_chars(cch_p, len);
}

String fx_String_acquire(char** ch_pp, size_t len) {
    String s__ = fx_String_null();
    if (len == 0 || *ch_pp == NULL) {
        return s__;
    }
    s__.data = *ch_pp;
    s__.len = len;
    s__.capacity = len;
    return s__;
}

extern inline String fx_String_from_chars(const char* chars, size_t len) {
    String s__ = fx_String_null();
    if (len == 0 || chars == NULL) {
        return s__;
    }
    _str_grow(&s__, len);
    memcpy(s__.data, chars, len);
    s__.len = len;
    return s__;
}

extern inline String fx_String_from_cstr(const char cstr[static 1]) {
    return fx_String_from_chars(cstr, strlen(cstr));
}

char* fx_String_to_cstr_copy(const String* str_p) {
    if (fx_String_is_null(str_p)) {
        return NULL;
    }
    char* cstr = fx_stdlib_malloc(str_p->len + 1);
    memcpy(str_p->data, cstr, str_p->len);
    cstr[str_p->len] = '\0';
    return cstr;
}

const char* fx_String_to_cstr(String* str_p) {
    if (fx_String_is_null(str_p)) {
        return NULL;
    }
    if (str_p->capacity < str_p->len + 1) {
        _str_grow(str_p, str_p->len + 1);
    }
    str_p->data[str_p->len] = '\0';
    return (const char*)str_p->data;
}

str fx_String_to_str(const String* str_p) {
    return (str){.data = str_p->data, .len = str_p->len};
}

/**
 * @brief Free a String
 * fx_stdlib_malloc', fx_stdlib_realloc' or `fx_stdlib_calloc'.
 * @return void
 */
void fx_String_free(String* str_p) {
    if (str_p->data) {
        fx_stdlib_free(str_p->data);
        str_p->data = NULL;
        str_p->len = 0;
        str_p->capacity = 0;
    }
}

/**
 * @brief Reserve a String
 * @param str_p pointer to the str
 * @param str_p pointer to the str
 * fx_stdlib_malloc', fx_stdlib_realloc' or `fx_stdlib_calloc'.
 * @return void
 */
void fx_String_reserve(String* str_p, size_t capacity) {
    if (str_p->capacity < capacity) {
        _str_grow(str_p, capacity);
    }
}

String fx_String_lsplit_by_String(String* str_p, const String* delim) {
    const str delim_view = fx_str_from_chars(delim->data, delim->len);
    return fx_String_lsplit_by_str(str_p, &delim_view);
}

String fx_String_lsplit_by_str(String* str_p, const str* delim) {
    char* substr = (char*)memmem(str_p->data, str_p->len, delim->data, delim->len);
    if (substr == NULL) {
        return fx_String_null();
    }
    size_t left_len = substr - str_p->data;
    String left = fx_String_from_chars(str_p->data, left_len);
    size_t right_len = str_p->len - left_len - delim->len;
    String right = fx_String_from_chars(substr + delim->len, right_len);
    fx_String_free(str_p);
    *str_p = right;
    return left;
}

String fx_String_lsplit_by_cstr(String* str_p, const char* cstr_delim) {
    str delim_view = fx_str_from_cstr(cstr_delim);
    return fx_String_lsplit_by_str(str_p, &delim_view);
}

String fx_String_lsplit_by_chr(String* str_p, const char cch_delim) {
    const str delim_view = fx_str_from_chars(&cch_delim, 1);
    return fx_String_lsplit_by_str(str_p, &delim_view);
}
