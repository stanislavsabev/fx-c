#include <criterion/criterion.h>
#include <stdio.h>
#include <string.h>

#include "strlib.h"
#include "util.h"

#ifdef FX_NO_SHORT_NAMES
#undef FX_NO_SHORT_NAMES
#endif

Test(str_buf_tests, fxstr_buf_null_create) {
    // test
    str_buf_t actual = fxstr_buf_null();

    // validate
    cr_expect(actual.data == NULL, "Expected actual.data == NULL");
    cr_expect(actual.len == 0, "Expected actual.len == 0");
    cr_expect(actual.capacity == 0, "Expected actual.capacity == 0");
}

Test(str_buf_tests, fxstr_buf_create_nominal) {
    // test
    const char* data = "abc";
    size_t ln = strlen(data);
    str_buf_t actual = fxstr_buf_create(data, ln);

    // validate
    cr_expect(actual.len == ln, "Expected actual.len == ln");
    cr_expect(actual.capacity >= ln, "Expected actual.capacity >= ln");
    cr_expect(strncmp(actual.data, data, ln) == 0, "Expected strncmp(actual.data, data, ln) == 0");
}

Test(str_buf_tests, fxstr_buf_acquire_nominal) {
    // test
    const char* data = "abc";
    size_t ln = strlen(data);

    char* buff = malloc(ln);
    memcpy(buff, "abc", ln);

    str_buf_t actual = fxstr_buf_acquire(&buff, ln);

    // validate
    cr_expect(actual.data == buff, "Expected same pointer: actual.data == buff");
    cr_expect(actual.len == ln, "Expected actual.len == ln");
    cr_expect(actual.capacity >= ln, "Expected actual.capacity >= ln");
    cr_expect(strncmp(actual.data, data, ln) == 0, "Expected strncmp(actual.data, data, ln) == 0");

    // change value to check if it's the same pointer
    memcpy(actual.data, "xyz", actual.len);
    cr_expect(strncmp(buff, "xyz", ln) == 0, "Expected strncmp(buff, \"xyz\", ln) == 0");

    // cleanup
    fxstr_buf_free(&actual);
}

Test(str_buf_tests, fxstr_buf_from_chars_create) {
    // setup
    const char* chars = "abcde";
    size_t ln = 3;

    // test
    str_buf_t actual = fxstr_buf_create(chars, ln);

    // validate
    cr_expect(strncmp(actual.data, chars, ln) == 0,
              "Expected strncmp(actual.data, chars, ln) == 0");
    cr_expect(actual.len == ln, "Expected actual.len == ln");
    cr_expect(actual.capacity >= ln, "Expected actual.capacity >= ln");

    // cleanup
    fxstr_buf_free(&actual);
}

Test(str_buf_tests, fxstr_buf_to_cstr_copy_create) {
    // setup
    str_buf_t strb = fxstr_buf_from_cstr("abc");

    // test
    char* actual = fxstr_buf_to_cstr_copy(&strb);

    // validate
    cr_expect(strncmp(actual, strb.data, strb.len) == 0);

    // cleanup
    free(actual);
    fxstr_buf_free(&strb);
}

Test(str_buf_tests, fxstr_buf_to_cstr_copy_from_null_is_null) {
    // setup
    str_buf_t strb = fxstr_buf_null();

    // test
    char* actual = fxstr_buf_to_cstr_copy(&strb);

    // validate
    cr_expect(actual == NULL, "Expect actual == NULL");
}

Test(str_buf_tests, fxstr_buf_to_cstr_ref_create) {
    // setup
    const char* cstr = "abcde";
    str_buf_t strb = fxstr_buf_from_cstr(cstr);
    // test
    const char* actual = fxstr_buf_to_cstr(&strb);

    // validate
    cr_expect(strncmp(actual, strb.data, strb.len) == 0);
    cr_expect(actual[strb.len] == '\0', "Expected actual[strb.len] = '\\0'");

    // cleanup
    fxstr_buf_free(&strb);
}

Test(str_buf_tests, fxstr_buf_to_cstr_ref_from_null_is_null) {
    // setup
    str_buf_t strb = fxstr_buf_null();

    // test
    const char* actual = fxstr_buf_to_cstr(&strb);

    // validate
    cr_expect(actual == NULL, "Expect actual == NULL");
}

Test(str_buf_tests, fxstr_buf_to_str_view_create) {
    // setup
    str_buf_t strb = fxstr_buf_from_cstr("abc");

    // test
    str_view_t actual = fxstr_buf_to_str_view(&strb);

    // validate
    cr_expect(strncmp(actual.data, strb.data, strb.len) == 0,
              "Expect strncmp(actual.data, strb.data, strb.len) == 0");
    cr_expect(actual.len == strb.len, "Expect actual.len == strb.len");

    // cleanup
    fxstr_buf_free(&strb);
}

Test(str_buf_tests, fxstr_buf_to_str_view_create_from_null_is_null) {
    // setup
    str_buf_t strb = fxstr_buf_null();

    // test
    str_view_t actual = fxstr_buf_to_str_view(&strb);

    // validate
    cr_expect(fxstr_view_is_null(&actual), "Expect fxstr_view_is_null(&actual)");
}

Test(str_buf_tests, fxstr_buf_free_nominal) {
    // setup
    str_buf_t strb = fxstr_buf_from_cstr("abc");

    // test
    fxstr_buf_free(&strb);

    // validate
    cr_expect(fxstr_buf_is_null(&strb), "Expect fxstr_buf_is_null(&strb)");
}

Test(str_buf_tests, fxstr_buf_reserve_nominal) {
    // setup
    str_buf_t strb = fxstr_buf_null();
    size_t cap = 8;

    // test
    fxstr_buf_reserve(&strb, cap);

    // validate
    cr_expect(!fxstr_buf_is_null(&strb), "Expect !fxstr_buf_is_null(&strb)");
    cr_expect(strb.capacity == cap, "Expect strb.capacity == cap");
    cr_expect(strb.data != NULL, "Expect strb.data != NULL");
    cr_expect(strb.len == 0, "Expect strb.len == 0");

    // cleanup
    fxstr_buf_free(&strb);
}
