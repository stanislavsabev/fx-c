#include <criterion/criterion.h>
#include <string.h>

#include "str.h"
#include "util.h"

#ifdef FX_NO_SHORT_NAMES
#undef FX_NO_SHORT_NAMES
#endif

Test(str_view_tests, fxstr_view_create_nominal) {
    char* chars = "abc";
    size_t ln = strlen(chars);
    str_view_t s = fxstr_view_create(chars, ln);

    cr_expect(s.len = ln, "Expected string s.len = ln");
    cr_expect((strncmp(chars, s.data, ln) == 0), "Expected strncmp(chars, s.data, ln) == 0");
}

Test(str_view_tests, fxstr_view_null_create) {
    str_view_t nulstr = fxstr_view_null();

    cr_expect(nulstr.data == NULL, "Expected fxstr.data == NULL");
    cr_expect(nulstr.len == 0, "Expected fxstr.len == 0");
}

Test(str_view_tests, fxstr_view_from_chars_create) {
    char* chars = "abc";
    size_t ln = strlen(chars);
    str_view_t s = fxstr_view_from_chars(chars, ln);

    cr_expect(s.len = ln, "Expected string s.len = ln");
    cr_expect((strncmp(chars, s.data, ln) == 0), "Expected strncmp(chars, s.data, ln) == 0");
}

Test(str_view_tests, fxstr_view_from_chars_create_partial) {
    char* chars = "abcdef";
    size_t ln = strlen("abc");
    str_view_t s = fxstr_view_from_chars(chars, ln);

    cr_expect(s.len = ln, "Expected string s.len = 3");
    cr_expect((strncmp("abc", s.data, ln) == 0), "Expected strncmp('abc', s.data, ln) == 0");
}

Test(str_view_tests, fxstr_view_from_cstr_create) {
    char* cstr = "hello";
    size_t ln = strlen(cstr);

    str_view_t s = fxstr_view_from_cstr(cstr);
    cr_expect(s.len = ln, "Expected string s.len = 5");
    cr_expect((strncmp(cstr, s.data, ln) == 0), "Expected strncmp(cstr, s.data, ln) == 0");
}

Test(str_view_tests, fxstr_view_to_cstr_create) {
    // setup
    char* cstr = "hello";
    size_t ln = strlen(cstr);
    str_view_t src = fxstr_view_from_cstr(cstr);

    // test
    char* actual = fxstr_view_to_cstr(&src);

    // validate
    cr_expect(strlen(actual) == src.len, "Expected strlen(actual) = src.len");
    cr_expect((strncmp(src.data, actual, ln) == 0),
              "Expected strncmp(src.data, actual.data, ln) == 0");
    cr_expect(actual[src.len] == '\0', "Expected actual[src->len] = '\\0'");

    // cleanup
    free(actual);
}
