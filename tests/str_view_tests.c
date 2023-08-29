#include <criterion/criterion.h>
#include <string.h>

#include "str.h"
#include "util.h"

#ifdef FX_NO_SHORT_NAMES
#undef FX_NO_SHORT_NAMES
#endif

Test(fxstrtests, fxstr_view_null_create) {
    str_view_t nulstr = fxstr_view_null();

    cr_expect(nulstr.data == NULL, "Expected fxstr.data == NULL");
    cr_expect(nulstr.len == 0, "Expected fxstr.len == 0");
}

Test(fxstrtests, fxstr_view_from_chars_create) {
    char* chars = "abc";
    size_t ln = strlen(chars);
    str_view_t s = fxstr_view_from_chars(ln, chars);

    cr_expect(s.len = ln, "Expected string s.len = ln");
    cr_expect((strncmp(chars, s.data, ln) == 0), "Expected strncmp(chars, s.data) == 0");

}

Test(fxstrtests, fxstr_view_from_chars_create_partial) {
    char* chars = "abcdef";
    size_t ln = strlen("abc");
    str_view_t s = fxstr_view_from_chars(ln, chars);

    cr_expect(s.len = ln, "Expected string s.len = 3");
    cr_expect((strncmp("abc", s.data, ln) == 0), "Expected strncmp('abc', s.data) == 0");

}

Test(fxstrtests, fxstr_view_from_cstr_create) {
    // fxstr_view_from_cstr

}

Test(fxstrtests, fxstr_view_to_cstr) {
    // fxstr_view_to_cstr

}

Test(fxstrtests, fx_memmem_find_substr) {
    // fx_memmem

}

Test(fxstrtests, fx_memmem_retrun_null_if_not_found) {
    // fx_memmem

}