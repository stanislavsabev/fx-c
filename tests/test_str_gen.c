#include <criterion/criterion.h>
#include <stdio.h>
#include <string.h>

#include "str.h"
#include "util.h"

#ifdef FX_NO_SHORT_NAMES
#undef FX_NO_SHORT_NAMES
#endif

Test(str_gen_tests, fxstr_len_nominal) {
    // setup
    size_t expected = 3;
    str_buf_t strb = fxstr_buf_from_chars("abc", expected);
    str_view_t strv = fxstr_view_from_chars("abc", expected);

    // test
    size_t actual_len_b = fxstr_len(&strb);
    size_t actual_len_v = fxstr_len(&strv);

    // validate
    cr_expect(actual_len_b == expected, "Expected actual_len_b == expected");
    cr_expect(actual_len_v == expected, "Expected actual_len_v == 0");

    // cleanup
    fxstr_buf_free(&strb);
}

Test(str_gen_tests, fxstr_len_null_str_len0) {
    // setup
    size_t expected = 0;

    str_buf_t strb = fxstr_buf_from_chars("", expected);
    str_view_t strv = fxstr_view_from_chars("", expected);

    // test
    size_t actual_len_b = fxstr_len(&strb);
    size_t actual_len_v = fxstr_len(&strv);

    // validate
    cr_expect(actual_len_b == expected, "Expected actual_len_b == expected");
    cr_expect(actual_len_v == expected, "Expected actual_len_v == expected");

    // cleanup
    fxstr_buf_free(&strb);
}

Test(str_gen_tests, fxstr_is_empty) {
    // setup
    bool expected = true;
    str_buf_t strb = fxstr_buf_create("", 0);
    str_view_t strv = fxstr_view_create("", 0);

    // test
    size_t actual_empty_b = fxstr_is_empty(&strb);
    size_t actual_empty_v = fxstr_is_empty(&strv);

    // validate
    cr_expect(actual_empty_b == expected, "Expected actual_len_b == expected");
    cr_expect(actual_empty_v == expected, "Expected actual_len_v == expected");

    // cleanup
    fxstr_buf_free(&strb);
}

Test(str_gen_tests, fxstr_is_null) {
    // setup
    str_buf_t strb = fxstr_buf_null();
    str_view_t strv = fxstr_view_null();

    // test
    bool actual_b = fxstr_is_null(&strb);
    bool actual_v = fxstr_is_null(&strv);

    // validate
    cr_expect(actual_b == true, "Expected actual_b == true");
    cr_expect(actual_v == true, "Expected actual_v == true");

    // cleanup
    fxstr_buf_free(&strb);
}

Test(str_gen_tests, fxstr_split_left_view_nominal) {
    // setup
    const char* delim = ".";
    char* data = "hello.world";
    size_t len = strlen(data);
    char* expect_left_data = "hello";
    size_t expect_left_len = strlen(expect_left_data);
    char* expect_right_data = "world";
    size_t expect_right_len = strlen(expect_right_data);
    size_t delim_len = strlen(delim);

    str_view_t str = fxstr_view_from_chars(data, len);

    // test
    str_view_t actual = fxstr_split_left(&str, delim);

    // validate
    cr_expect(actual.len == expect_left_len, "Expected actual.len == expect_left_len");
    cr_expect(strncmp(actual.data, expect_left_data, expect_left_len) == 0,
              "Expected strncmp(actual.data, expect_left_data, expect_left_len) == 0");

    cr_expect(str.len == expect_right_len, "Expected str.len == expect_right_len");
    cr_expect(strncmp(str.data, expect_right_data, expect_right_len) == 0,
              "Expected strncmp(str.data, expect_right_data, expect_left_len) == 0");

    cr_expect(actual.len + str.len == len - delim_len,
              "Expected actual.len + str.len == len - delim_len");
}

Test(str_gen_tests, fxstr_split_left_buf_nominal) {
    // setup
    char* delim = ".";
    char* data = "hello.world";
    size_t len = strlen(data);
    char* expect_left_data = "hello";
    size_t expect_left_len = strlen(expect_left_data);
    char* expect_right_data = "world";
    size_t expect_right_len = strlen(expect_right_data);
    size_t delim_len = strlen(delim);

    str_buf_t str = fxstr_buf_from_chars(data, len);

    // test
    str_buf_t actual = fxstr_split_left(&str, delim);

    // validate
    cr_expect(actual.len == expect_left_len, "Expected actual.len == expect_left_len");
    cr_expect(strncmp(actual.data, expect_left_data, expect_left_len) == 0,
              "Expected strncmp(actual.data, expect_left_data, expect_left_len) == 0");
    cr_expect(str.len == expect_right_len, "Expected str.len == expect_right_len");
    cr_expect(strncmp(str.data, expect_right_data, expect_right_len) == 0,
              "Expected strncmp(str.data, expect_right_data, expect_left_len) == 0");
    cr_expect(actual.len + str.len == len - delim_len,
              "Expected actual.len + strv.len == len - delim_len");

    // // cleanup
    fxstr_buf_free(&str);
    fxstr_buf_free(&actual);
}

Test(str_gen_tests, fxstr_split_left_view_non_existing) {
    // setup
    char* delim = ".";
    char* data = "hello_world";
    size_t len = strlen(data);

    str_view_t str = fxstr_view_from_chars(data, len);

    // test
    str_view_t actual = fxstr_split_left(&str, delim);

    // validate
    cr_expect(actual.len == 0, "Expected actual.len == 0");
    cr_expect(actual.data == NULL, "Expected actual.data == NULL");
    cr_expect(fxstr_is_null(&actual));
}

Test(str_gen_tests, fxstr_split_left_buf_non_existing) {
    // setup
    const char* delim = ".";
    char* data = "hello_world";
    size_t len = strlen(data);

    str_buf_t str = fxstr_buf_from_chars(data, len);

    // test
    str_buf_t actual = fxstr_split_left(&str, delim);

    // validate
    cr_expect(actual.len == 0, "Expected actual.len == 0");
    cr_expect(actual.data == NULL, "Expected actual.data == NULL");
    cr_expect(fxstr_is_null(&actual));

    // // cleanup
    fxstr_buf_free(&str);
    fxstr_buf_free(&actual);
}

Test(str_gen_tests, fxstr_view_split_left_chr_nominal) {
    // setup
    const char delim = '\n';
    char* data = "hello\nworld";
    size_t len = strlen(data);
    char* expect_left_data = "hello";
    size_t expect_left_len = strlen(expect_left_data);
    char* expect_right_data = "world";
    size_t expect_right_len = strlen(expect_right_data);

    str_view_t str = fxstr_view_from_chars(data, len);

    // test
    str_view_t actual = fxstr_split_left(&str, delim);

    // validate
    cr_expect(actual.len == expect_left_len, "Expected actual.len == expect_left_len");
    cr_expect(strncmp(actual.data, expect_left_data, expect_left_len) == 0,
              "Expected strncmp(actual.data, expect_left_data, expect_left_len) == 0");

    cr_expect(str.len == expect_right_len, "Expected str.len == expect_right_len");
    cr_expect(strncmp(str.data, expect_right_data, expect_right_len) == 0,
              "Expected strncmp(str.data, expect_right_data, expect_left_len) == 0");

    cr_expect(actual.len + str.len == len - 1, "Expected actual.len + str.len == len - 1");
}

Test(str_gen_tests, fxstr_buf_split_left_chr_nominal) {
    // setup
    const char delim = '\n';
    char* data = "hello\nworld";
    size_t len = strlen(data);
    char* expect_left_data = "hello";
    size_t expect_left_len = strlen(expect_left_data);
    char* expect_right_data = "world";
    size_t expect_right_len = strlen(expect_right_data);

    str_buf_t str = fxstr_buf_from_chars(data, len);

    // test
    str_buf_t actual = fxstr_split_left(&str, delim);

    // validate
    cr_expect(actual.len == expect_left_len, "Expected actual.len == expect_left_len");
    cr_expect(strncmp(actual.data, expect_left_data, expect_left_len) == 0,
              "Expected strncmp(actual.data, expect_left_data, expect_left_len) == 0");

    cr_expect(str.len == expect_right_len, "Expected str.len == expect_right_len");
    cr_expect(strncmp(str.data, expect_right_data, expect_right_len) == 0,
              "Expected strncmp(str.data, expect_right_data, expect_left_len) == 0");

    cr_expect(actual.len + str.len == len - 1, "Expected actual.len + str.len == len - 1");
}

Test(str_gen_tests, fxstr_split_left_buf_delim_at_the_end) {
    // setup
    const char* delim = "\n";
    char* data = "hello world\n";
    size_t len = strlen(data);
    char* expect_left_data = "hello world";
    size_t expect_left_len = strlen(expect_left_data);

    str_buf_t str = fxstr_buf_from_chars(data, len);

    // test
    str_buf_t actual = fxstr_split_left(&str, delim);

    // validate
    cr_expect(actual.len == expect_left_len, "Expected actual.len == expect_left_len");
    cr_expect(strncmp(actual.data, expect_left_data, expect_left_len) == 0,
              "Expected strncmp(actual.data, expect_left_data, expect_left_len) == 0");
    cr_expect(fxstr_is_null(&str), "Expected fxstr_is_null(&str)");

    // // cleanup
    fxstr_buf_free(&str);
    fxstr_buf_free(&actual);
}

Test(str_gen_tests, fxstr_split_left_view_delim_at_the_end) {
    // setup
    const char* delim = "\n";
    char* data = "hello world\n";
    size_t len = strlen(data);
    char* expect_left_data = "hello world";
    size_t expect_left_len = strlen(expect_left_data);

    str_view_t str = fxstr_view_from_chars(data, len);

    // test
    str_view_t actual = fxstr_split_left(&str, delim);

    // validate
    cr_expect(actual.len == expect_left_len, "Expected actual.len == expect_left_len");
    cr_expect(strncmp(actual.data, expect_left_data, expect_left_len) == 0,
              "Expected strncmp(actual.data, expect_left_data, expect_left_len) == 0");
    cr_expect(fxstr_is_null(&str), "Expected fxstr_is_null(&str)");
}

Test(str_gen_tests, fxstr_view_split_left_chr_delim_at_the_end) {
    // setup
    const char delim = '\n';
    char* data = "hello\n";
    size_t len = strlen(data);
    char* expect_left_data = "hello";
    size_t expect_left_len = strlen(expect_left_data);

    str_view_t str = fxstr_view_from_chars(data, len);

    // test
    str_view_t actual = fxstr_split_left(&str, delim);

    // validate
    cr_expect(actual.len == expect_left_len, "Expected actual.len == expect_left_len");
    cr_expect(strncmp(actual.data, expect_left_data, expect_left_len) == 0,
              "Expected strncmp(actual.data, expect_left_data, expect_left_len) == 0");
    cr_expect(fxstr_is_null(&str), "Expected fxstr_is_null(&str)");
}

Test(str_gen_tests, fxstr_buf_split_left_chr_delim_at_the_end) {
    // setup
    const char delim = '\n';
    char* data = "hello\n";
    size_t len = strlen(data);
    char* expect_left_data = "hello";
    size_t expect_left_len = strlen(expect_left_data);

    str_buf_t str = fxstr_buf_from_chars(data, len);

    // test
    str_buf_t actual = fxstr_split_left(&str, delim);

    // validate
    cr_expect(actual.len == expect_left_len, "Expected actual.len == expect_left_len");
    cr_expect(strncmp(actual.data, expect_left_data, expect_left_len) == 0,
              "Expected strncmp(actual.data, expect_left_data, expect_left_len) == 0");
    cr_expect(fxstr_is_null(&str), "Expected fxstr_is_null(&str)");
}

// TODO: Test when delimiter is beginning of input

Test(str_gen_tests, fxstr_split_left_buf_delim_at_beginning) {
    // setup
    const char* delim = "\n";
    char* data = "\nhello world";
    size_t len = strlen(data);
    char* expect_data = "hello world";
    size_t expect_len = strlen(expect_data);

    str_buf_t str = fxstr_buf_from_chars(data, len);

    // test
    str_buf_t actual = fxstr_split_left(&str, delim);

    // validate
    cr_expect(fxstr_is_null(&actual), "Expected fxstr_is_null(&actual)");
    cr_expect(str.len == expect_len, "Expected str.len == expect_len");
    cr_expect(strncmp(str.data, expect_data, expect_len) == 0,
              "Expected strncmp(str.data, expect_data, expect_len) == 0");

    // // cleanup
    fxstr_buf_free(&str);
    fxstr_buf_free(&actual);
}

Test(str_gen_tests, fxstr_split_left_view_delim_at_beginning) {
    // setup
    const char* delim = "\n";
    char* data = "\nhello world";
    size_t len = strlen(data);
    char* expect_data = "hello world";
    size_t expect_len = strlen(expect_data);

    str_view_t str = fxstr_view_from_chars(data, len);

    // test
    str_view_t actual = fxstr_split_left(&str, delim);

    // validate
    cr_expect(fxstr_is_null(&actual), "Expected fxstr_is_null(&actual)");
    cr_expect(str.len == expect_len, "Expected str.len == expect_len");
    cr_expect(strncmp(str.data, expect_data, expect_len) == 0,
              "Expected strncmp(str.data, expect_data, expect_len) == 0");
}

Test(str_gen_tests, fxstr_view_split_left_chr_delim_at_beginning) {
    // setup
    const char delim = '\n';
    char* data = "\nhello";
    size_t len = strlen(data);
    char* expect_data = "hello";
    size_t expect_len = strlen(expect_data);

    str_view_t str = fxstr_view_from_chars(data, len);

    // test
    str_view_t actual = fxstr_split_left(&str, delim);

    // validate
    cr_expect(fxstr_is_null(&actual), "Expected fxstr_is_null(&actual)");
    cr_expect(str.len == expect_len, "Expected str.len == expect_len");
    cr_expect(strncmp(str.data, expect_data, expect_len) == 0,
              "Expected strncmp(str.data, expect_data, expect_len) == 0");
}

Test(str_gen_tests, fxstr_buf_split_left_chr_delim_at_beginning) {
    // setup
    const char delim = '\n';
    char* data = "\nhello";
    size_t len = strlen(data);
    char* expect_data = "hello";
    size_t expect_len = strlen(expect_data);

    str_buf_t str = fxstr_buf_from_chars(data, len);

    // test
    str_buf_t actual = fxstr_split_left(&str, delim);

    // validate
    cr_expect(fxstr_is_null(&actual), "Expected fxstr_is_null(&actual)");
    cr_expect(str.len == expect_len, "Expected str.len == expect_len");
    cr_expect(strncmp(str.data, expect_data, expect_len) == 0,
              "Expected strncmp(str.data, expect_data, expect_len) == 0");
}