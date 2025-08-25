#include <criterion/criterion.h>
#include <stdio.h>
#include <string.h>

#include "strlib.h"
#include "util.h"

#ifdef FXLIB_NO_SHORT_NAMES
#undef FXLIB_NO_SHORT_NAMES
#endif

Test(str_gen_tests, strlib_len_nominal) {
    // setup
    size_t expected = 3;
    String strb = String_from_chars("abc", expected);
    str strv = strlib_str_from_chars("abc", expected);

    // test
    size_t actual_len_b = strlib_len(&strb);
    size_t actual_len_v = strlib_len(&strv);

    // validate
    cr_expect(actual_len_b == expected, "Expected actual_len_b == expected");
    cr_expect(actual_len_v == expected, "Expected actual_len_v == 0");

    // cleanup
    strlib_String_free(&strb);
}

Test(str_gen_tests, strlib_len_null_str_len0) {
    // setup
    size_t expected = 0;

    String string = String_from_chars("", expected);
    str s = strlib_str_from_chars("", expected);

    // test
    size_t actual_len_b = strlib_len(&string);
    size_t actual_len_v = strlib_len(&s);

    // validate
    cr_expect(actual_len_b == expected, "Expected actual_len_b == expected");
    cr_expect(actual_len_v == expected, "Expected actual_len_v == expected");

    // cleanup
    strlib_String_free(&string);
}

Test(str_gen_tests, strlib_is_empty) {
    // setup
    bool expected = true;
    String strb = String_create("", 0);
    str strv = strlib_str_create("", 0);

    // test
    size_t actual_empty_b = strlib_is_empty(&strb);
    size_t actual_empty_v = strlib_is_empty(&strv);

    // validate
    cr_expect(actual_empty_b == expected, "Expected actual_len_b == expected");
    cr_expect(actual_empty_v == expected, "Expected actual_len_v == expected");

    // cleanup
    strlib_String_free(&strb);
}

Test(str_gen_tests, strlib_is_null) {
    // setup
    String string = String_null();
    str s = strlib_str_null();

    // test
    bool actual_string = strlib_is_null(&string);
    bool actual_str = strlib_is_null(&s);

    // validate
    cr_expect(actual_string == true, "Expected actual_string == true");
    cr_expect(actual_str == true, "Expected actual_str == true");

    // cleanup
    strlib_String_free(&string);
}

Test(str_gen_tests, str_lsplit_nominal) {
    // setup
    const char* delim = ".";
    char* data = "hello.world";
    size_t len = strlen(data);
    char* expect_left_data = "hello";
    size_t expect_left_len = strlen(expect_left_data);
    char* expect_right_data = "world";
    size_t expect_right_len = strlen(expect_right_data);
    size_t delim_len = strlen(delim);

    str s = fx_str_from_chars(data, len);

    // test
    str actual = str_lsplit(&s, delim);

    // validate
    cr_expect(actual.len == expect_left_len, "Expected actual.len == expect_left_len");
    cr_expect(strncmp(actual.data, expect_left_data, expect_left_len) == 0,
              "Expected strncmp(actual.data, expect_left_data, expect_left_len) == 0");

    cr_expect(s.len == expect_right_len, "Expected s.len == expect_right_len");
    cr_expect(strncmp(s.data, expect_right_data, expect_right_len) == 0,
              "Expected strncmp(s.data, expect_right_data, expect_left_len) == 0");

    cr_expect(actual.len + s.len == len - delim_len,
              "Expected actual.len + s.len == len - delim_len");
}

Test(str_gen_tests, fxstr_lsplit_buf_nominal) {
    // setup
    char* delim = ".";
    char* data = "hello.world";
    size_t len = strlen(data);
    char* expect_left_data = "hello";
    size_t expect_left_len = strlen(expect_left_data);
    char* expect_right_data = "world";
    size_t expect_right_len = strlen(expect_right_data);
    size_t delim_len = strlen(delim);

    String s = String_from_chars(data, len);

    // test
    String actual = String_lsplit(&s, delim);

    // validate
    cr_expect(actual.len == expect_left_len, "Expected actual.len == expect_left_len");
    cr_expect(strncmp(actual.data, expect_left_data, expect_left_len) == 0,
              "Expected strncmp(actual.data, expect_left_data, expect_left_len) == 0");
    cr_expect(s.len == expect_right_len, "Expected s.len == expect_right_len");
    cr_expect(strncmp(s.data, expect_right_data, expect_right_len) == 0,
              "Expected strncmp(s.data, expect_right_data, expect_left_len) == 0");
    cr_expect(actual.len + s.len == len - delim_len,
              "Expected actual.len + strv.len == len - delim_len");

    // // cleanup
    fx_String_free(&s);
    fx_String_free(&actual);
}

Test(str_gen_tests, str_lsplit__non_existing) {
    // setup
    char* delim = ".";
    char* data = "hello_world";
    size_t len = strlen(data);

    str s = str_from_chars(data, len);

    // test
    str actual = str_lsplit_by_cstr(&s, delim);

    // validate
    cr_expect(actual.len == 0, "Expected actual.len == 0");
    cr_expect(actual.data == NULL, "Expected actual.data == NULL");
    cr_expect(fx_is_null(&actual));
}

Test(str_gen_tests, fxstr_lsplit_by_cstr_non_existing) {
    // setup
    const char* delim = ".";
    char* data = "hello_world";
    size_t len = strlen(data);

    String s = String_from_chars(data, len);

    // test
    String actual = String_lsplit_by_cstr(&s, delim);

    // validate
    cr_expect(actual.len == 0, "Expected actual.len == 0");
    cr_expect(actual.data == NULL, "Expected actual.data == NULL");
    cr_expect(fx_is_null(&actual));

    // // cleanup
    String_free(&s);
    String_free(&actual);
}

Test(str_gen_tests, str_split_left_by_chr_nominal) {
    // setup
    const char delim = '\n';
    char* data = "hello\nworld";
    size_t len = strlen(data);
    char* expect_left_data = "hello";
    size_t expect_left_len = strlen(expect_left_data);
    char* expect_right_data = "world";
    size_t expect_right_len = strlen(expect_right_data);

    str s = strlib_str_from_chars(data, len);

    // test
    str actual = strlib_str_lsplit_by_chr(&s, delim);

    // validate
    cr_expect(actual.len == expect_left_len, "Expected actual.len == expect_left_len");
    cr_expect(strncmp(actual.data, expect_left_data, expect_left_len) == 0,
              "Expected strncmp(actual.data, expect_left_data, expect_left_len) == 0");

    cr_expect(s.len == expect_right_len, "Expected s.len == expect_right_len");
    cr_expect(strncmp(s.data, expect_right_data, expect_right_len) == 0,
              "Expected strncmp(s.data, expect_right_data, expect_left_len) == 0");

    cr_expect(actual.len + s.len == len - 1, "Expected actual.len + s.len == len - 1");
}

Test(str_gen_tests, String_split_left_chr_nominal) {
    // setup
    const char delim = '\n';
    char* data = "hello\nworld";
    size_t len = strlen(data);
    char* expect_left_data = "hello";
    size_t expect_left_len = strlen(expect_left_data);
    char* expect_right_data = "world";
    size_t expect_right_len = strlen(expect_right_data);

    String s = String_from_chars(data, len);

    // test
    String actual = strlib_String_lsplit_by_chr(&s, delim);

    // validate
    cr_expect(actual.len == expect_left_len, "Expected actual.len == expect_left_len");
    cr_expect(strncmp(actual.data, expect_left_data, expect_left_len) == 0,
              "Expected strncmp(actual.data, expect_left_data, expect_left_len) == 0");

    cr_expect(s.len == expect_right_len, "Expected s.len == expect_right_len");
    cr_expect(strncmp(s.data, expect_right_data, expect_right_len) == 0,
              "Expected strncmp(s.data, expect_right_data, expect_left_len) == 0");

    cr_expect(actual.len + s.len == len - 1, "Expected actual.len + s.len == len - 1");
}

Test(str_gen_tests, fxstr_lsplit_buf_delim_at_the_end) {
    // setup
    const char* delim = "\n";
    char* data = "hello world\n";
    size_t len = strlen(data);
    char* expect_left_data = "hello world";
    size_t expect_left_len = strlen(expect_left_data);

    String s = String_from_chars(data, len);

    // test
    String actual = String_lsplit(&s, delim);

    // validate
    cr_expect(actual.len == expect_left_len, "Expected actual.len == expect_left_len");
    cr_expect(strncmp(actual.data, expect_left_data, expect_left_len) == 0,
              "Expected strncmp(actual.data, expect_left_data, expect_left_len) == 0");
    cr_expect(strlib_is_null(&s), "Expected strlib_is_null(&s)");

    // // cleanup
    strlib_String_free(&s);
    strlib_String_free(&actual);
}

Test(str_gen_tests, str_lsplit__delim_at_the_end) {
    // setup
    const char* delim = "\n";
    char* data = "hello world\n";
    size_t len = strlen(data);
    char* expect_left_data = "hello world";
    size_t expect_left_len = strlen(expect_left_data);

    str s = strlib_str_from_chars(data, len);

    // test
    str actual = str_lsplit(&s, delim);

    // validate
    cr_expect(actual.len == expect_left_len, "Expected actual.len == expect_left_len");
    cr_expect(strncmp(actual.data, expect_left_data, expect_left_len) == 0,
              "Expected strncmp(actual.data, expect_left_data, expect_left_len) == 0");
    cr_expect(strlib_is_null(&s), "Expected strlib_is_null(&s)");
}

Test(str_gen_tests, str_split_left_by_chr_delim_at_the_end) {
    // setup
    const char delim = '\n';
    char* data = "hello\n";
    size_t len = strlen(data);
    char* expect_left_data = "hello";
    size_t expect_left_len = strlen(expect_left_data);

    str s = strlib_str_from_chars(data, len);

    // test
    str actual = strlib_str_lsplit_by_chr(&s, delim);

    // validate
    cr_expect(actual.len == expect_left_len, "Expected actual.len == expect_left_len");
    cr_expect(strncmp(actual.data, expect_left_data, expect_left_len) == 0,
              "Expected strncmp(actual.data, expect_left_data, expect_left_len) == 0");
    cr_expect(strlib_is_null(&s), "Expected strlib_is_null(&s)");
}

Test(str_gen_tests, String_split_left_chr_delim_at_the_end) {
    // setup
    const char delim = '\n';
    char* data = "hello\n";
    size_t len = strlen(data);
    char* expect_left_data = "hello";
    size_t expect_left_len = strlen(expect_left_data);

    String s = String_from_chars(data, len);

    // test
    String actual = strlib_String_lsplit_by_chr(&s, delim);

    // validate
    cr_expect(actual.len == expect_left_len, "Expected actual.len == expect_left_len");
    cr_expect(strncmp(actual.data, expect_left_data, expect_left_len) == 0,
              "Expected strncmp(actual.data, expect_left_data, expect_left_len) == 0");
    cr_expect(strlib_is_null(&s), "Expected strlib_is_null(&s)");
}

// TODO: Test when delimiter is beginning of input

Test(str_gen_tests, fxstr_lsplit_buf_delim_at_beginning) {
    // setup
    const char* delim = "\n";
    char* data = "\nhello world";
    size_t len = strlen(data);
    char* expect_data = "hello world";
    size_t expect_len = strlen(expect_data);

    String s = String_from_chars(data, len);

    // test
    String actual = String_lsplit(&s, delim);

    // validate
    cr_expect(strlib_is_null(&actual), "Expected strlib_is_null(&actual)");
    cr_expect(s.len == expect_len, "Expected s.len == expect_len");
    cr_expect(strncmp(s.data, expect_data, expect_len) == 0,
              "Expected strncmp(s.data, expect_data, expect_len) == 0");

    // // cleanup
    strlib_String_free(&s);
    strlib_String_free(&actual);
}

Test(str_gen_tests, str_lsplit__delim_at_beginning) {
    // setup
    const char* delim = "\n";
    char* data = "\nhello world";
    size_t len = strlen(data);
    char* expect_data = "hello world";
    size_t expect_len = strlen(expect_data);

    str s = strlib_str_from_chars(data, len);

    // test
    str actual = str_lsplit(&s, delim);

    // validate
    cr_expect(strlib_is_null(&actual), "Expected strlib_is_null(&actual)");
    cr_expect(s.len == expect_len, "Expected s.len == expect_len");
    cr_expect(strncmp(s.data, expect_data, expect_len) == 0,
              "Expected strncmp(s.data, expect_data, expect_len) == 0");
}

Test(str_gen_tests, str_split_left_by_chr_delim_at_beginning) {
    // setup
    const char delim = '\n';
    char* data = "\nhello";
    size_t len = strlen(data);
    char* expect_data = "hello";
    size_t expect_len = strlen(expect_data);

    str s = strlib_str_from_chars(data, len);

    // test
    str actual = strlib_str_lsplit_by_chr(&s, delim);

    // validate
    cr_expect(strlib_is_null(&actual), "Expected strlib_is_null(&actual)");
    cr_expect(s.len == expect_len, "Expected s.len == expect_len");
    cr_expect(strncmp(s.data, expect_data, expect_len) == 0,
              "Expected strncmp(s.data, expect_data, expect_len) == 0");
}

Test(str_gen_tests, String_split_left_chr_delim_at_beginning) {
    // setup
    const char delim = '\n';
    char* data = "\nhello";
    size_t len = strlen(data);
    char* expect_data = "hello";
    size_t expect_len = strlen(expect_data);

    String s = String_from_chars(data, len);

    // test
    String actual = strlib_String_lsplit_by_chr(&s, delim);

    // validate
    cr_expect(strlib_is_null(&actual), "Expected strlib_is_null(&actual)");
    cr_expect(s.len == expect_len, "Expected s.len == expect_len");
    cr_expect(strncmp(s.data, expect_data, expect_len) == 0,
              "Expected strncmp(s.data, expect_data, expect_len) == 0");
}