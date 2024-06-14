#include <assert.h>
#include <string.h>

#include "strlib.h"
#include "util.h"

extern inline str strlib_str_null(void) {
    return strlib_str_from_chars(NULL, 0);
}

extern inline str strlib_str_create(const char* data, size_t len) {
    return strlib_str_from_chars(data, len);
}

extern inline str strlib_str_from_chars(const char* chars, size_t len) {
    return (str){.len = len, .data = chars};
}

extern inline str strlib_str_from_cstr(const char cstr[static 1]) {
    return strlib_str_from_chars(cstr, strlen(cstr));
}

char* strlib_str_to_cstr(const str* str_p) {
    char* cstr = strlib_stdlib_malloc(str_p->len + 1);
    memcpy(cstr, str_p->data, str_p->len);
    cstr[str_p->len] = '\0';
    return cstr;
}

str strlib_str_lsplit_view(str* str_p, const str* delim) {
    char* substr = (char*)fx_memmem(str_p->data, str_p->len, delim->data, delim->len);
    if (substr == NULL) {
        return strlib_str_null();
    }
    size_t left_len = substr - str_p->data;
    str left = strlib_str_null();
    if (left_len > 0) {
        left = strlib_str_from_chars(str_p->data, left_len);
    }
    str_p->len -= left_len + delim->len;
    if (str_p->len == 0) {
        str_p->data = NULL;
    } else {
        str_p->data = substr + delim->len;
    }
    return left;
}

str strlib_str_lsplit_buf(str* str_p, const String* delim) {
    const str delim_view = strlib_str_from_chars(delim->data, delim->len);
    return strlib_str_lsplit_view(str_p, &delim_view);
}

str strlib_str_lsplit_cstr(str* str_p, const char* delim) {
    const str delim_view = strlib_str_from_cstr(delim);
    return strlib_str_lsplit_view(str_p, &delim_view);
}

str strlib_str_lsplit_chr(str* str_p, const char cch_delim) {
    const str delim_view = strlib_str_from_chars(&cch_delim, 1);
    return strlib_str_lsplit_view(str_p, &delim_view);
}