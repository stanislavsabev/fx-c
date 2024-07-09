#include <criterion/criterion.h>
#include <stdio.h>
#include <string.h>

#include "strlib.h"
#include "util.h"

#ifdef FXLIB_NO_SHORT_NAMES
#undef FXLIB_NO_SHORT_NAMES
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
    String string = String_from_cstr("abc");

    // test
    char* actual = String_to_cstr_copy(&string);

    // validate
    cr_expect(strncmp(actual, string.data, string.len) == 0);

    // cleanup
    free(actual);
    String_free(&string);
}

Test(String_tests, String_to_cstr_copy_from_null_is_null) {
    // setup
    String string = String_null();

    // test
    char* actual = String_to_cstr_copy(&string);

    // validate
    cr_expect(actual == NULL, "Expect actual == NULL");
}

Test(String_tests, String_to_cstr_ref_create) {
    // setup
    const char* cstr = "abcde";
    String string = String_from_cstr(cstr);
    // test
    const char* actual = String_to_cstr(&string);

    // validate
    cr_expect(strncmp(actual, string.data, string.len) == 0);
    cr_expect(actual[string.len] == '\0', "Expected actual[string.len] = '\\0'");

    // cleanup
    String_free(&string);
}

Test(String_tests, String_to_cstr_ref_from_null_is_null) {
    // setup
    String string = String_null();

    // test
    const char* actual = String_to_cstr(&string);

    // validate
    cr_expect(actual == NULL, "Expect actual == NULL");
}

Test(String_tests, String_to_str_create) {
    // setup
    String string = String_from_cstr("abc");

    // test
    str actual = String_to_str(&string);

    // validate
    cr_expect(strncmp(actual.data, string.data, string.len) == 0,
              "Expect strncmp(actual.data, string.data, string.len) == 0");
    cr_expect(actual.len == string.len, "Expect actual.len == string.len");

    // cleanup
    String_free(&string);
}

Test(String_tests, String_to_str_create_from_null_is_null) {
    // setup
    String string = String_null();

    // test
    str actual = String_to_str(&string);

    // validate
    cr_expect(strlib_is_null(&actual), "Expect strlib_String_is_null(&actual)");
}

Test(String_tests, String_free_nominal) {
    // setup
    String string = String_from_cstr("abc");

    // test
    String_free(&string);

    // validate
    cr_expect(String_is_null(&string), "Expect String_is_null(&string)");
}

Test(String_tests, String_reserve_nominal) {
    // setup
    String string = String_null();
    size_t cap = 8;

    // test
    String_reserve(&string, cap);

    // validate
    cr_expect(!String_is_null(&string), "Expect !String_is_null(&string)");
    cr_expect(string.capacity == cap, "Expect string.capacity == cap");
    cr_expect(string.data != NULL, "Expect string.data != NULL");
    cr_expect(string.len == 0, "Expect string.len == 0");

    // cleanup
    String_free(&string);
}
