#include <assert.h>
#include <string.h>

#include "str.h"

extern inline str_view_t fxstr_view_null(void) {
    return (str_view_t){.len = 0, .data = NULL};
}

extern inline str_view_t fxstr_view_from_chars(size_t len, const char chars[static len]) {
    return (str_view_t){.len = len, .data = chars};
}

extern inline str_view_t fxstr_view_from_cstr(const char cstr[static 1]) {
    return fxstr_view_from_chars(strlen(cstr), cstr);
}

char* fxstr_view_to_cstr(const str_view_t* str_p) {
    char* cstr = fxstr_stdlib_malloc(str_p->len + 1);
    memcpy(cstr, str_p->data, str_p->len);
    cstr[str_p->len] = '\0';
    return cstr;
}
