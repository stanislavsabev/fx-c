#ifndef _fx_H_
#define _fx_H_

#include <stdbool.h>
#include <stdlib.h>

// Memory functions
#ifndef fx_stdlib_free
#define fx_stdlib_free free /* free function */
#endif
#ifndef fx_stdlib_malloc
#define fx_stdlib_malloc malloc
#endif
#ifndef fx_stdlib_calloc
#define fx_stdlib_calloc calloc
#endif
#ifndef fx_stdlib_realloc
#define fx_stdlib_realloc realloc
#endif

/**
 * @brief struct with len and char data[]
 */
typedef struct {
    size_t len;
    const char* data;
} str;

/**
 * @brief struct with len and char data[64]
 */
typedef struct {
    size_t capacity;
    size_t len;
    char* data;
} String;

#ifndef FXLIB_NO_SHORT_NAMES

// str
#define str_null                   fx_str_null
#define str_create(data, len)      fx_str_create(data, len)
#define str_len(str_p)             fx_str_len(str_p)
#define str_is_empty(str_p)        fx_str_is_empty(str_p)
#define str_is_null(str_p)         fx_str_is_null(str_p)
#define str_from_chars(chars, len) fx_str_from_chars(chars, len)
#define str_from_cstr(cstr)        fx_str_from_cstr(cstr)
#define str_to_cstr(str_p)         fx_str_to_cstr(str_p)
// #define str_lsplit(str_p, delim)   fx_str_lsplit(str_p, delim)

#define str_lsplit_by_str(str_p, delim)    fx_str_lsplit_by_str(str_p, delim)
#define str_lsplit_by_String(str_p, delim) fx_str_lsplit_by_String(str_p, delim)
#define str_lsplit_by_cstr(str_p, delim)   fx_str_lsplit_by_cstr(str_p, delim)
#define str_lsplit_by_chr(str_p, delim)    fx_str_lsplit_by_chr(str_p, delim)

// String
#define String_null                     fx_String_null
#define String_create(cch_p, len)       fx_String_create(cch_p, len)
#define String_acquire(ch_pp, len)      fx_String_acquire(ch_pp, len)
#define String_len(str_p)               fx_String_len(str_p)
#define String_is_empty(str_p)          fx_String_is_empty(str_p)
#define String_is_null(str_p)           fx_String_is_null(str_p)
#define String_from_chars(chars, len)   fx_String_from_chars(chars, len)
#define String_from_cstr(cstr)          fx_String_from_cstr(cstr)
#define String_to_cstr(str_p)           fx_String_to_cstr(str_p)
#define String_to_cstr_copy(str_p)      fx_String_to_cstr_copy(str_p)
#define String_to_str(str_p)            fx_String_to_str(str_p)
#define String_free(str_p)              fx_String_free(str_p)
#define String_reserve(str_p, capacity) fx_String_reserve(str_p, capacity)

// lsplit
#define String_lsplit_by_String(str_p, delim) fx_String_lsplit_by_String(str_p, delim)
#define String_lsplit_by_str(str_p, delim)    fx_String_lsplit_by_str(str_p, delim)
#define String_lsplit_by_cstr(str_p, delim)   fx_String_lsplit_by_cstr(str_p, delim)
#define String_lsplit_by_chr(str_p, delim)    fx_String_lsplit_by_chr(str_p, delim)

#endif   // FXLIB_NO_SHORT_NAMES

// str
str fx_str_null(void);
str fx_str_create(const char* data, size_t len);

static inline size_t fx_str_len(const str* str_p) {
    return str_p->len;
}
static inline bool fx_str_is_empty(const str* str_p) {
    return fx_str_len(str_p) == 0;
}
static inline bool fx_str_is_null(const str* str_p) {
    return str_p->len == 0 && str_p->data == NULL;
}
str fx_str_from_chars(const char* chars, size_t len);
str fx_str_from_cstr(const char cstr[static 1]);
char* fx_str_to_cstr(const str* str_p);

// view split left
str fx_str_lsplit_by_str(str* str_p, const str* delim);
str fx_str_lsplit_by_String(str* str_p, const String* delim);
str fx_str_lsplit_by_cstr(str* str_p, const char* delim);
str fx_str_lsplit_by_chr(str* str_p, const char char_delim);

// String
String fx_String_null(void);
String fx_String_create(const char* cch_p, size_t len);
String fx_String_acquire(char** ch_pp, size_t len);

static inline size_t fx_String_len(const String* str_p) {
    return str_p->len;
}
static inline bool fx_String_is_empty(const String* str_p) {
    return fx_String_len(str_p) == 0;
}
static inline bool fx_String_is_null(const String* str_p) {
    return str_p->len == 0 && str_p->data == NULL;
}
String fx_String_from_chars(const char* chars, size_t len);
String fx_String_from_cstr(const char cstr[static 1]);
const char* fx_String_to_cstr(String* str_p);
char* fx_String_to_cstr_copy(const String* str_p);
str fx_String_to_str(const String* str_p);
void fx_String_free(String* str_p);
void fx_String_reserve(String* str_p, size_t capacity);

// buf split left
String fx_String_lsplit_by_String(String* str_p, const String* delim);
String fx_String_lsplit_by_str(String* str_p, const str* delim);
String fx_String_lsplit_by_cstr(String* str_p, const char* cstr_delim);
String fx_String_lsplit_by_chr(String* str_p, const char char_delim);

#endif   // _fx_H_
