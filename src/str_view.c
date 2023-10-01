#include <assert.h>
#include <string.h>

#include "str.h"
#include "util.h"

extern inline str_view_t fxstr_view_null(void) {
    return fxstr_view_from_chars(NULL, 0);
}

extern inline str_view_t fxstr_view_create(const char* data, size_t len) {
    return fxstr_view_from_chars(data, len);
}

extern inline str_view_t fxstr_view_from_chars(const char* chars, size_t len) {
    return (str_view_t){.len = len, .data = chars};
}

extern inline str_view_t fxstr_view_from_cstr(const char cstr[static 1]) {
    return fxstr_view_from_chars(cstr, strlen(cstr));
}

char* fxstr_view_to_cstr(const str_view_t* str_p) {
    char* cstr = fxstr_stdlib_malloc(str_p->len + 1);
    memcpy(cstr, str_p->data, str_p->len);
    cstr[str_p->len] = '\0';
    return cstr;
}

str_view_t fxstr_view_split_left_view(str_view_t* str_p, const str_view_t* delim) {
    char* substr = (char*)fx_memmem(str_p->data, str_p->len, delim->data, delim->len);
    if (substr == NULL) {
        return fxstr_view_null();
    }
    size_t left_len = substr - str_p->data;
    str_view_t left = fxstr_view_null();
    if (left_len > 0) {
        left = fxstr_view_from_chars(str_p->data, left_len);
    }
    str_p->len -= left_len + delim->len;
    if (str_p->len == 0) {
        str_p->data = NULL;
    } else {
        str_p->data = substr + delim->len;
    }
    return left;
}

str_view_t fxstr_view_split_left_buf(str_view_t* str_p, const str_buf_t* delim) {
    const str_view_t delim_view = fxstr_view_from_chars(delim->data, delim->len);
    return fxstr_view_split_left_view(str_p, &delim_view);
}

str_view_t fxstr_view_split_left_cstr(str_view_t* str_p, const char* delim) {
    const str_view_t delim_view = fxstr_view_from_cstr(delim);
    return fxstr_view_split_left_view(str_p, &delim_view);
}

str_view_t fxstr_view_split_left_chr(str_view_t* str_p, const char delim) {
    const str_view_t delim_view = fxstr_view_from_chars(&delim, 1);
    return fxstr_view_split_left_view(str_p, &delim_view);
}