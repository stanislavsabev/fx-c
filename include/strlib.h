#ifndef _STRLIB_H_
#define _STRLIB_H_

#include <stdbool.h>
#include <stdlib.h>

// Memory functions
#ifndef strlib_stdlib_free
#define strlib_stdlib_free free /* free function */
#endif
#ifndef strlib_stdlib_malloc
#define strlib_stdlib_malloc malloc
#endif
#ifndef strlib_stdlib_calloc
#define strlib_stdlib_calloc calloc
#endif
#ifndef strlib_stdlib_realloc
#define strlib_stdlib_realloc realloc
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

// str
#define strv_null                        strlib_str_null
#define strv_create(data, len)           strlib_str_create(data, len)
#define strv_len(str_p)                  strlib_str_len(str_p)
#define strv_is_empty(str_p)             strlib_str_is_empty(str_p)
#define strv_is_null(str_p)              strlib_str_is_null(str_p)
#define strv_from_chars(chars, len)      strlib_str_from_chars(chars, len)
#define strv_from_cstr(cstr)             strlib_str_from_cstr(cstr)
#define strv_to_cstr(str_p)              strlib_str_to_cstr(str_p)
#define strv_lsplit(str_p, delim)        strlib_str_lsplit(str_p, delim)
#define strv_lsplit_chr(str_p, delim)    strlib_str_lsplit_chr(str_p, cch_delim)

// String
#define String_null                        strlib_String_null
#define String_create(cch_p, len)          strlib_String_create(cch_p, len)
#define String_acquire(ch_pp, len)         strlib_String_acquire(ch_pp, len)
#define String_len(str_p)                  strlib_String_len(str_p)
#define String_is_empty(str_p)             strlib_String_is_empty(str_p)
#define String_is_null(str_p)              strlib_String_is_null(str_p)
#define String_from_chars(chars, len)      strlib_String_from_chars(chars, len)
#define String_from_cstr(cstr)             strlib_String_from_cstr(cstr)
#define String_to_cstr(str_p)              strlib_String_to_cstr(str_p)
#define String_to_cstr_copy(str_p)         strlib_String_to_cstr_copy(str_p)
#define String_to_str(str_p)               strlib_String_to_str(str_p)
#define String_free(str_p)                 strlib_String_free(str_p)
#define String_reserve(str_p, capacity)    strlib_String_reserve(str_p, capacity)
#define String_lsplit(str_p, delim)        strlib_String_lsplit(str_p, delim)
#define String_lsplit_chr(str_p, delim)    strlib_String_lsplit_chr(str_p, cch_delim)

// Common
#define str_len(str_p)                   fxstr_len(str_p)
#define str_is_empty(str_p)              fxstr_is_empty(str_p)
#define str_is_null(str_p)               fxstr_is_null(str_p)
#define str_lsplit(str_p, delim)         fxstr_lsplit(str_p, delim)
#define str_lsplit_chr(str_p, cch_delim) fxstr_lsplit_chr(str_p, cch_delim)

#endif   // STRLIB_NO_SHORT_NAMES

// str
str strlib_str_null(void);
str strlib_str_create(const char* data, size_t len);

static inline size_t strlib_str_len(const str* str_p) {
    return str_p->len;
}
static inline bool strlib_str_is_empty(const str* str_p) {
    return strlib_str_len(str_p) == 0;
}
static inline bool strlib_str_is_null(const str* str_p) {
    return str_p->len == 0 && str_p->data == NULL;
}
str strlib_str_from_chars(const char* chars, size_t len);
str strlib_str_from_cstr(const char cstr[static 1]);
char* strlib_str_to_cstr(const str* fxstr_);

// view split left
str strlib_str_lsplit_view(str* str_p, const str* delim);
str strlib_str_lsplit_buf(str* str_p, const String* delim);
str strlib_str_lsplit_cstr(str* str_p, const char* delim);
str strlib_str_lsplit_chr(str* str_p, const char cch_delim);

// String
String strlib_String_null(void);
String strlib_String_create(const char* cch_p, size_t len);
String strlib_String_acquire(char** ch_pp, size_t len);

static inline size_t strlib_String_len(const String* str_p) {
    return str_p->len;
}
static inline bool strlib_String_is_empty(const String* str_p) {
    return strlib_String_len(str_p) == 0;
}
static inline bool strlib_String_is_null(const String* str_p) {
    return str_p->len == 0 && str_p->data == NULL;
}
String strlib_String_from_chars(const char* chars, size_t len);
String strlib_String_from_cstr(const char cstr[static 1]);
const char* strlib_String_to_cstr(String* str_p);
char* strlib_String_to_cstr_copy(const String* str_p);
str strlib_String_to_str(const String* str_p);
void strlib_String_free(String* str_p);
void strlib_String_reserve(String* str_p, size_t capacity);

// buf split left
String strlib_String_lsplit_buf(String* str_p, const String* delim);
String strlib_String_lsplit_view(String* str_p, const str* delim);
String strlib_String_lsplit_cstr(String* str_p, const char* delim);
String strlib_String_lsplit_chr(String* str_p, const char cch_delim);

// generic
#define fxstr_len(str_p) \
    _Generic((str_p), str * : strlib_str_len, String * : strlib_String_len)(str_p)

#define fxstr_is_empty(str_p) \
    _Generic((str_p), str * : strlib_str_is_empty, String * : strlib_String_is_empty)(str_p)

#define fxstr_is_null(str_p) \
    _Generic((str_p), str * : strlib_str_is_null, String * : strlib_String_is_null)(str_p)

// clang-format off
#define strlib_str_split_left_(delim)             \
    _Generic((delim),                             \
            str* : strlib_str_lsplit_view, \
            String*  : strlib_str_lsplit_buf,  \
            char*       : strlib_str_lsplit_cstr, \
            const char* : strlib_str_lsplit_cstr  \
    )

#define strlib_String_split_left_(delim)             \
    _Generic((delim),                            \
            String*  : strlib_String_lsplit_buf,  \
            str* : strlib_String_lsplit_view, \
            char*       : strlib_String_lsplit_cstr, \
            const char* : strlib_String_lsplit_cstr  \
    )

#define strlib_String_lsplit(str_p, delim)  strlib_String_split_left_(delim)(str_p, delim)
#define strlib_str_lsplit(str_p, delim) strlib_str_split_left_(delim)(str_p, delim)

#define fxstr_lsplit(str_p, delim)                       \
    _Generic((str_p),                                    \
            str* : strlib_str_split_left_(delim), \
            String * : strlib_String_split_left_(delim))(str_p, delim)

#define fxstr_lsplit_chr(str_p, cch_delim)           \
    _Generic((str_p),                            \
            str* : strlib_str_lsplit_chr, \
            String * : strlib_String_lsplit_chr)(str_p, cch_delim)
// clang-format on

#endif   // _STRLIB_H_
