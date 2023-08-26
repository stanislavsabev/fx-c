#ifndef FX_FXSTR_H_
#define FX_FXSTR_H_

#include <stdbool.h>
#include <stdlib.h>

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

#define str        fxstr_t
#define str_buf64  fxstr_buf64_t
#define str_buf256 fxstr_buf256_t
#define str_null   fxstr_null

#endif   // FX_NO_SHORT_NAMES

#endif   // FX_FXSTR_H_

// ------------------------------------------------------------------------------------------
//  IMPLEMENTATION
// ------------------------------------------------------------------------------------------
#ifdef FX_IMPLEMENTATION

fxstr_t fxstr_split_cstr(fxstr_t str, const char* delim, size_t n) {
}

char* fxstr_to_cstr(fxstr_t str) {
}

#endif   // FX_IMPLEMENTATION
