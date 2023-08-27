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
 * @brief For internal use. Grows the fxstr data.
 * @param fxstr_p__ pointer to the fxstr
 * @return void
 */
void _fxstr_grow(str_buf_t *str_p_, size_t capacity_) {
    const size_t ln__ = capacity_ * sizeof(*str_p_->data);
    if (str_p_->data) {
        void *data_p2__ = fxstr_stdlib_realloc(str_p_->data, ln__);
        assert(data_p2__);
        str_p_->data = data_p2__;
    } else {
        char *fxstr_p__ = fxstr_stdlib_malloc(ln__);
        assert(fxstr_p__);
        str_p_->data = fxstr_p__;
        str_p_->len = 0;
    }
    str_p_->capacity = capacity_;
}

extern inline str_buf_t fxstr_buf_null(void) {
    return (str_buf_t){.capacity = _FXSTR_INITIAL_CAPACITY, .len = 0, .data = NULL};
}

str_buf_t fxstr_buf_from_chars(size_t len_, const char chars_[static len_]) {
    str_buf_t s__ = fxstr_buf_null();
    if (len_ == 0) {
        return s__;
    }
    _fxstr_grow(&s__, len_);
    memcpy(s__.data, chars_, s__.len);
    s__.len = len_;
    return s__;
}

extern inline str_buf_t fxstr_buf_from_cstr(const char cstr[static 1]) {
    return fxstr_buf_from_chars(strlen(cstr), cstr);
}

char *fxstr_buf_to_cstr(const str_buf_t *str_ptr_) {
    char *cstr = fxstr_stdlib_malloc(str_ptr_->len + 1);
    memcpy(cstr, str_ptr_->data, str_ptr_->len);
    cstr[str_ptr_->len] = '\0';
    return cstr;
}

/**
 * @brief Free an fxstr allocated by
 * fxstr_stdlib_malloc', fxstr_stdlib_realloc' or `fxstr_stdlib_calloc'.
 * @return void
 */
void fxstr_buf_free(str_buf_t *str_) {
    if (str_->data) {
        fxstr_stdlib_free(str_->data);
    }
}
