#ifndef FX_FXSTR_H_
#define FX_FXSTR_H_

#include <stdlib.h>
#include <stdbool.h>

// Memory functions
#ifndef fxstr_stdlib_free
#define fxstr_stdlib_free free /* free function */
#endif
#ifndef fxstr_stdlib_malloc
#define fxstr_stdlib_malloc malloc
#endif
#ifndef fxstr_stdlib_calloc
#define fxstr_stdlib_calloc calloc
#endif
#ifndef fxstr_stdlib_realloc
#define fxstr_stdlib_realloc realloc
#endif

/**
 * @brief struct with len and char data[]
 */
typedef struct fxstr_s {
    size_t capacity;
    size_t len;
    char* data;
} fxstr_t;

/**
 * @brief struct with len and char data[64]
 */
typedef struct fxstr_buf64_s {
    size_t len;
    char data[64];
} fxstr_buf64_t;

/**
 * @brief struct with len and char data[256]
 */
typedef struct fxstr_buf256_s {
    size_t len;
    char data[256];
} fxstr_buf256_t;

#ifndef FX_NO_SHORT_NAMES

#define str              fxstr_t
#define str_buf64        fxstr_buf64_t
#define str_buf256       fxstr_buf256_t
#define str_null         fxstr_null
#define str_from_literal fxstr_from_literal

#endif   // FX_NO_SHORT_NAMES

#define _FXSTR_GROW_MULTIPLIER  2
#define _FXSTR_INITIAL_CAPACITY 1

static inline fxstr_t fxstr_null(void) {
    return (fxstr_t){.capacity = 0, .len = 0, .data = NULL};
}

static inline bool fxstr_is_empty(const fxstr_t fxstr_) {
    return fxstr_len(fxstr_) == 0;
}

static inline size_t fxstr_len(const fxstr_t fxstr_) {
    return fxstr_.len;
}

fxstr_t fxstr_from_cstr(const char* cstr[static 1]);
char* fxstr_to_cstr(const fxstr_t* fxstr_);

#endif   // FX_FXSTR_H_

// ------------------------------------------------------------------------------------------
//  IMPLEMENTATION
// ------------------------------------------------------------------------------------------
#ifdef FXSTR_IMPLEMENTATION

fxstr_t fxstr_from_cstr(const char* cstr[static 1]) {
    size_t ln__ = strlen(cstr) - 1;   // drop the '\0'
    return fxstr_from_chars(ln__, cstr);
}

char* fxstr_to_cstr(const fxstr_t* fxstr_) {
    if (!fxstr_->capacity > fxstr_->len) {
        _fxstr_grow(&fxstr_, fxstr_->len + 1);   // one more the '\0'
    }
    fxstr_->data[fxstr_->len] = '\0';
    return fxstr_->data;
}


#endif   // FXSTR_IMPLEMENTATION
