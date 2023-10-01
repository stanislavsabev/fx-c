#ifndef FX_FXSTR_H_
#define FX_FXSTR_H_

#include <stdbool.h>
#include <stdlib.h>

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
typedef struct str_veiw_s {
    size_t len;
    const char* data;
} str_view_t;

/**
 * @brief struct with len and char data[64]
 */
typedef struct str_buf_s {
    size_t capacity;
    size_t len;
    char* data;
} str_buf_t;

/**
 * @brief struct with len and char data[64]
 */
typedef struct str_buf64_s {
    size_t len;
    char data[64];
} str_buf64_t;

/**
 * @brief struct with len and char data[256]
 */
typedef struct str_buf256_s {
    size_t len;
    char data[256];
} str_buf256_t;

#ifndef FX_NO_SHORT_NAMES

#define strv_null                    fxstr_view_null
#define str_len(str_p)               fxstr_len(str_p)
#define str_is_empty(str_p)          fxstr_is_empty(str_p)
#define strv_len(str_p)              fxstr_view_len(str_p)
#define strv_is_empty(str_p)         fxstr_view_is_empty(str_p)
#define strv_from_chars(chars, len)  fxstr_view_from_chars(chars, len)
#define strv_from_cstr(cstr)         fxstr_view_from_cstr(cstr)
#define strv_to_cstr(str_p)          fxstr_view_to_cstr(str_p)
#define strb_null                    fxstr_buf_null
#define strb_len(str_p)              fxstr_buf_len(str_p)
#define strb_free(str_p)             fxstr_buf_free(str_p)
#define strb_from_chars(chars, len)  fxstr_buf_from_chars(chars, len)
#define strb_from_cstr(cstr)         fxstr_buf_from_cstr(cstr)
#define strb_to_cstr(str_p)          fxstr_buf_to_cstr(str_p)

#endif   // FX_NO_SHORT_NAMES

// str_view_t
str_view_t fxstr_view_create(const char* data, size_t len);
str_view_t fxstr_view_null(void);
static inline size_t fxstr_view_len(const str_view_t* str_p) {
    return str_p->len;
}
static inline bool fxstr_view_is_empty(const str_view_t* str_p) {
    return fxstr_view_len(str_p) == 0;
}
static inline bool fxstr_view_is_null(const str_view_t* str_p) {
    return str_p->len == 0 && str_p->data == NULL;
}
str_view_t fxstr_view_from_chars(const char* chars, size_t len);
str_view_t fxstr_view_from_cstr(const char cstr[static 1]);
char* fxstr_view_to_cstr(const str_view_t* fxstr_);

// view split left
str_view_t fxstr_view_split_left_view(str_view_t* str_p, const str_view_t* delim);
str_view_t fxstr_view_split_left_buf(str_view_t* str_p, const str_buf_t* delim);
str_view_t fxstr_view_split_left_cstr(str_view_t* str_p, const char* delim);

// str_buf_t
str_buf_t fxstr_buf_create(const char* data, size_t len);
str_buf_t fxstr_buf_null(void);
static inline size_t fxstr_buf_len(const str_buf_t* str_p) {
    return str_p->len;
}
static inline bool fxstr_buf_is_empty(const str_buf_t* str_p) {
    return fxstr_buf_len(str_p) == 0;
}
static inline bool fxstr_buf_is_null(const str_buf_t* str_p) {
    return str_p->len == 0 && str_p->data == NULL;
}
str_buf_t fxstr_buf_from_chars(const char* chars, size_t len);
str_buf_t fxstr_buf_from_cstr(const char cstr[static 1]);
char* fxstr_buf_to_cstr_ref(str_buf_t* str_p);
char* fxstr_buf_to_cstr_copy(const str_buf_t* str_p);
str_view_t fxstr_buf_to_str_view(const str_buf_t* str_p);
void fxstr_buf_free(str_buf_t* str_p);
void fxstr_buf_reserve(str_buf_t* str_p, size_t capacity);

// buf split left
str_buf_t fxstr_buf_split_left_buf(str_buf_t* str_p, const str_buf_t* delim);
str_buf_t fxstr_buf_split_left_view(str_buf_t* str_p, const str_view_t* delim);
str_buf_t fxstr_buf_split_left_cstr(str_buf_t* str_p, const char* delim);

// generic
#define fxstr_len(str_p) \
    _Generic((str_p), str_view_t * : fxstr_view_len, str_buf_t * : fxstr_buf_len)(str_p)

#define fxstr_is_empty(str_p) \
    _Generic((str_p), str_view_t * : fxstr_view_is_empty, str_buf_t * : fxstr_buf_is_empty)(str_p)

#define fxstr_is_null(str_p) \
    _Generic((str_p), str_view_t * : fxstr_view_is_null, str_buf_t * : fxstr_buf_is_null)(str_p)

// TODO: Implement split by char
#define fxstr_view_split_left_(delim) \
    _Generic((delim),                                 \
            str_view_t* : fxstr_view_split_left_view, \
            str_buf_t* : fxstr_view_split_left_buf,   \
            char* : fxstr_view_split_left_cstr)

// TODO: Implement split by char
#define fxstr_buf_split_left_(delim) \
    _Generic((delim),                                \
            str_buf_t* : fxstr_buf_split_left_buf,   \
            str_view_t* : fxstr_buf_split_left_view, \
            char* : fxstr_buf_split_left_cstr)

#define fxstr_buf_split_left(str_p, delim)  fxstr_buf_split_left_(delim)(str_p, delim)
#define fxstr_view_split_left(str_p, delim) fxstr_view_split_left_(delim)(str_p, delim)

// clang-format off
#define fxstr_split_left(str_p, delim)                   \
    _Generic((str_p),                                    \
            str_view_t* : fxstr_view_split_left_(delim), \
            str_buf_t * : fxstr_buf_split_left_(delim))(str_p, delim)
// clang-format on

#endif   // FX_FXSTR_H_
