#include <string.h>
#include <assert.h>

#include "str.h"

/**
 * @brief For internal use. Grows the fxstr data.
 * @param fxstr_p__ pointer to the fxstr
 * @return void
 */
void _fxstr_grow(fxstr_t* fxstr_p_, size_t len_) {
    assert(len_ > 0);
    if(fxstr_p_->len >= len_){
        return;
    }

    if (fxstr_p_->data) {
        void* data_p2__ = fxstr_stdlib_realloc(fxstr_p_->data, len_);
        assert(data_p2__);
        fxstr_p_->data = data_p2__;
    } else {
        char* fxstr_p__ = fxstr_stdlib_malloc(len_);
        assert(fxstr_p__);
        fxstr_p_->data = fxstr_p__;
    }
    fxstr_p_->len = len_;
}


fxstr_t fxstr_from_chars(size_t len_, const char chars_[static len_]) {
    fxstr_t s__ = fxstr_null();
    if (len_ == 0) {
        return s__;
    }
    _fxstr_grow(&s__, len_);
    memcpy(s__.data, chars_, s__.len);
    s__.len = len_;
    return s__;
}

fxstr_t fxstr_from_cstr(const char cstr[static 1]) {
    size_t ln__ = strlen(cstr) - 1;   // drop the '\0'
    return fxstr_from_chars(ln__, cstr);

}

char* fxstr_to_cstr(const fxstr_t* fxstr_) {
    char* cstr = fxstr_stdlib_malloc(fxstr_->len + 1);
    memcpy(cstr, fxstr_->data, fxstr_->len);
    cstr[fxstr_->len] = '\0';
    return cstr;
}

/**
 * @brief Free an fxstr allocated by
 * fxstr_stdlib_malloc', fxstr_stdlib_realloc' or `fxstr_stdlib_calloc'.
 * @return void
 */
void fxstr_free(fxstr_t* fxstr_) {
    if (fxstr_->data) {
        free(fxstr_->data);
    }
}