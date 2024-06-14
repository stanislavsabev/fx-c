#include <criterion/criterion.h>
#include <stdio.h>
#include <string.h>

#include "strlib.h"
#include "util.h"

#ifdef STRLIB_NO_SHORT_NAMES
#undef STRLIB_NO_SHORT_NAMES
#endif

Test(String_tests, String_null_create) {
    // test
    String actual = String_null();

    // validate
    cr_expect(actual.data == NULL, "Expected actual.data == NULL");
    cr_expect(actual.len == 0, "Expected actual.len == 0");
    cr_expect(actual.capacity == 0, "Expected actual.capacity == 0");
}

Test(String_tests, String_create_nominal) {
    // test
    const char* data = "abc";
    size_t ln = strlen(data);
    String actual = String_create(data, ln);

    // validate
    cr_expect(actual.len == ln, "Expected actual.len == ln");
    cr_expect(actual.capacity >= ln, "Expected actual.capacity >= ln");
    cr_expect(strncmp(actual.data, data, ln) == 0, "Expected strncmp(actual.data, data, ln) == 0");
}

Test(String_tests, String_acquire_nominal) {
    // test
    const char* data = "abc";
    size_t ln = strlen(data);

    char* buff = malloc(ln);
    memcpy(buff, "abc", ln);

    String actual = String_acquire(&buff, ln);

    // validate
    cr_expect(actual.data == buff, "Expected same pointer: actual.data == buff");
    cr_expect(actual.len == ln, "Expected actual.len == ln");
    cr_expect(actual.capacity >= ln, "Expected actual.capacity >= ln");
    cr_expect(strncmp(actual.data, data, ln) == 0, "Expected strncmp(actual.data, data, ln) == 0");

    // change value to check if it's the same pointer
    memcpy(actual.data, "xyz", actual.len);
    cr_expect(strncmp(buff, "xyz", ln) == 0, "Expected strncmp(buff, \"xyz\", ln) == 0");

    // cleanup
    String_free(&actual);
}

Test(String_tests, String_from_chars_create) {
    // setup
    const char* chars = "abcde";
    size_t ln = 3;

    // test
    String actual = String_create(chars, ln);

    // validate
    cr_expect(strncmp(actual.data, chars, ln) == 0,
              "Expected strncmp(actual.data, chars, ln) == 0");
    cr_expect(actual.len == ln, "Expected actual.len == ln");
    cr_expect(actual.capacity >= ln, "Expected actual.capacity >= ln");

    // cleanup
    String_free(&actual);
}

Test(String_tests, String_to_cstr_copy_create) {
    // setup
    String strb = String_from_cstr("abc");

    // test
    char* actual = String_to_cstr_copy(&strb);

    // validate
    cr_expect(strncmp(actual, strb.data, strb.len) == 0);

    // cleanup
    free(actual);
    String_free(&strb);
}

Test(String_tests, String_to_cstr_copy_from_null_is_null) {
    // setup
    String strb = String_null();

    // test
    char* actual = String_to_cstr_copy(&strb);

    // validate
    cr_expect(actual == NULL, "Expect actual == NULL");
}

Test(String_tests, String_to_cstr_ref_create) {
    // setup
    const char* cstr = "abcde";
    String strb = String_from_cstr(cstr);
    // test
    const char* actual = String_to_cstr(&strb);

    // validate
    cr_expect(strncmp(actual, strb.data, strb.len) == 0);
    cr_expect(actual[strb.len] == '\0', "Expected actual[strb.len] = '\\0'");

    // cleanup
    String_free(&strb);
}

Test(String_tests, String_to_cstr_ref_from_null_is_null) {
    // setup
    String strb = String_null();

    // test
    const char* actual = String_to_cstr(&strb);

    // validate
    cr_expect(actual == NULL, "Expect actual == NULL");
}

Test(String_tests, String_to_str_create) {
    // setup
    String strb = String_from_cstr("abc");

    // test
    str actual = String_to_str(&strb);

    // validate
    cr_expect(strncmp(actual.data, strb.data, strb.len) == 0,
              "Expect strncmp(actual.data, strb.data, strb.len) == 0");
    cr_expect(actual.len == strb.len, "Expect actual.len == strb.len");

    // cleanup
    String_free(&strb);
}

Test(String_tests, String_to_str_create_from_null_is_null) {
    // setup
    String strb = String_null();

    // test
    str actual = String_to_str(&strb);

    // validate
    cr_expect(strv_is_null(&actual), "Expect strv_is_null(&actual)");
}

Test(String_tests, String_free_nominal) {
    // setup
    String strb = String_from_cstr("abc");

    // test
    String_free(&strb);

    // validate
    cr_expect(String_is_null(&strb), "Expect String_is_null(&strb)");
}

Test(String_tests, String_reserve_nominal) {
    // setup
    String strb = String_null();
    size_t cap = 8;

    // test
    String_reserve(&strb, cap);

    // validate
    cr_expect(!String_is_null(&strb), "Expect !String_is_null(&strb)");
    cr_expect(strb.capacity == cap, "Expect strb.capacity == cap");
    cr_expect(strb.data != NULL, "Expect strb.data != NULL");
    cr_expect(strb.len == 0, "Expect strb.len == 0");

    // cleanup
    String_free(&strb);
}
