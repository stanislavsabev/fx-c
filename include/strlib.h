#ifndef _STRLIB_H_
#define _STRLIB_H_

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
typedef struct str_s {
    size_t len;
    const char* data;
} str;

/**
 * @brief struct with len and char data[64]
 */
typedef struct String_s {
    size_t capacity;
    size_t len;
    char* data;
} String;


#ifndef STRLIB_NO_SHORT_NAMES

#define strv_null                        fxstr_view_null
#define strv_create(data, len)           fxstr_view_create(data, len)
#define strv_len(str_p)                  fxstr_view_len(str_p)
#define strv_is_empty(str_p)             fxstr_view_is_empty(str_p)
#define strv_is_null(str_p)              fxstr_view_is_null(str_p)
#define strv_from_chars(chars, len)      fxstr_view_from_chars(chars, len)
#define strv_from_cstr(cstr)             fxstr_view_from_cstr(cstr)
#define strv_to_cstr(str_p)              fxstr_view_to_cstr(str_p)
#define strv_lsplit(str_p, delim)        fxstr_view_lsplit(str_p, delim)
#define strv_lsplit_chr(str_p, delim)    fxstr_view_lsplit_chr(str_p, cch_delim)
#define strb_null                        fxstr_buf_null
#define strb_create(cch_p, len)          fxstr_buf_create(cch_p, len)
#define strb_acquire(ch_pp, len)         fxstr_buf_acquire(ch_pp, len)
#define strb_len(str_p)                  fxstr_buf_len(str_p)
#define strb_is_empty(str_p)             fxstr_buf_is_empty(str_p)
#define strb_is_null(str_p)              fxstr_buf_is_null(str_p)
#define strb_from_chars(chars, len)      fxstr_buf_from_chars(chars, len)
#define strb_from_cstr(cstr)             fxstr_buf_from_cstr(cstr)
#define strb_to_cstr(str_p)              fxstr_buf_to_cstr(str_p)
#define strb_to_cstr_copy(str_p)         fxstr_buf_to_cstr_copy(str_p)
#define strb_to_str_view(str_p)          fxstr_buf_to_str_view(str_p)
#define strb_free(str_p)                 fxstr_buf_free(str_p)
#define strb_reserve(str_p, capacity)    fxstr_buf_reserve(str_p, capacity)
#define strb_lsplit(str_p, delim)        fxstr_buf_lsplit(str_p, delim)
#define strb_lsplit_chr(str_p, delim)    fxstr_buf_lsplit_chr(str_p, cch_delim)
#define str_len(str_p)                   fxstr_len(str_p)
#define str_is_empty(str_p)              fxstr_is_empty(str_p)
#define str_is_null(str_p)               fxstr_is_null(str_p)
#define str_lsplit(str_p, delim)         fxstr_lsplit(str_p, delim)
#define str_lsplit_chr(str_p, cch_delim) fxstr_lsplit_chr(str_p, cch_delim)

#endif   // STRLIB_NO_SHORT_NAMES

// str
str fxstr_view_null(void);
str fxstr_view_create(const char* data, size_t len);

static inline size_t fxstr_view_len(const str* str_p) {
    return str_p->len;
}
static inline bool fxstr_view_is_empty(const str* str_p) {
    return fxstr_view_len(str_p) == 0;
}
static inline bool fxstr_view_is_null(const str* str_p) {
    return str_p->len == 0 && str_p->data == NULL;
}
str fxstr_view_from_chars(const char* chars, size_t len);
str fxstr_view_from_cstr(const char cstr[static 1]);
char* fxstr_view_to_cstr(const str* fxstr_);

// view split left
str fxstr_view_lsplit_view(str* str_p, const str* delim);
str fxstr_view_lsplit_buf(str* str_p, const String* delim);
str fxstr_view_lsplit_cstr(str* str_p, const char* delim);
str fxstr_view_lsplit_chr(str* str_p, const char cch_delim);

// String
String fxstr_buf_null(void);
String fxstr_buf_create(const char* cch_p, size_t len);
String fxstr_buf_acquire(char** ch_pp, size_t len);

static inline size_t fxstr_buf_len(const String* str_p) {
    return str_p->len;
}
static inline bool fxstr_buf_is_empty(const String* str_p) {
    return fxstr_buf_len(str_p) == 0;
}
static inline bool fxstr_buf_is_null(const String* str_p) {
    return str_p->len == 0 && str_p->data == NULL;
}
String fxstr_buf_from_chars(const char* chars, size_t len);
String fxstr_buf_from_cstr(const char cstr[static 1]);
const char* fxstr_buf_to_cstr(String* str_p);
char* fxstr_buf_to_cstr_copy(const String* str_p);
str fxstr_buf_to_str_view(const String* str_p);
void fxstr_buf_free(String* str_p);
void fxstr_buf_reserve(String* str_p, size_t capacity);

// buf split left
String fxstr_buf_lsplit_buf(String* str_p, const String* delim);
String fxstr_buf_lsplit_view(String* str_p, const str* delim);
String fxstr_buf_lsplit_cstr(String* str_p, const char* delim);
String fxstr_buf_lsplit_chr(String* str_p, const char cch_delim);

// generic
#define fxstr_len(str_p) \
    _Generic((str_p), str * : fxstr_view_len, String * : fxstr_buf_len)(str_p)

#define fxstr_is_empty(str_p) \
    _Generic((str_p), str * : fxstr_view_is_empty, String * : fxstr_buf_is_empty)(str_p)

#define fxstr_is_null(str_p) \
    _Generic((str_p), str * : fxstr_view_is_null, String * : fxstr_buf_is_null)(str_p)

// clang-format off
#define fxstr_view_split_left_(delim)             \
    _Generic((delim),                             \
            str* : fxstr_view_lsplit_view, \
            String*  : fxstr_view_lsplit_buf,  \
            char*       : fxstr_view_lsplit_cstr, \
            const char* : fxstr_view_lsplit_cstr  \
    )

#define fxstr_buf_split_left_(delim)             \
    _Generic((delim),                            \
            String*  : fxstr_buf_lsplit_buf,  \
            str* : fxstr_buf_lsplit_view, \
            char*       : fxstr_buf_lsplit_cstr, \
            const char* : fxstr_buf_lsplit_cstr  \
    )

#define fxstr_buf_lsplit(str_p, delim)  fxstr_buf_split_left_(delim)(str_p, delim)
#define fxstr_view_lsplit(str_p, delim) fxstr_view_split_left_(delim)(str_p, delim)

#define fxstr_lsplit(str_p, delim)                       \
    _Generic((str_p),                                    \
            str* : fxstr_view_split_left_(delim), \
            String * : fxstr_buf_split_left_(delim))(str_p, delim)

#define fxstr_lsplit_chr(str_p, cch_delim)           \
    _Generic((str_p),                            \
            str* : fxstr_view_lsplit_chr, \
            String * : fxstr_buf_lsplit_chr)(str_p, cch_delim)
// clang-format on

#endif   // _STRLIB_H_
