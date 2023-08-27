#include "str.h"

#include <assert.h>
#include <string.h>

extern inline str_view_t fxstr_view_null(void) {
    return (str_view_t){.len = 0, .data = NULL};
}

extern inline str_view_t fxstr_view_from_chars(size_t len_, const char chars_[static len_]) {
    return (str_view_t){.len = len_, .data = chars_};
}

extern inline str_view_t fxstr_view_from_cstr(const char cstr[static 1]) {
    return fxstr_view_from_chars(strlen(cstr), cstr);
}

char *fxstr_view_to_cstr(const str_view_t *fxstr_) {
    char *cstr = fxstr_stdlib_malloc(fxstr_->len + 1);
    memcpy(cstr, fxstr_->data, fxstr_->len);
    cstr[fxstr_->len] = '\0';
    return cstr;
}
