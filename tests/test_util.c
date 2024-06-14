#include <criterion/criterion.h>
#include <criterion/logging.h>
#include <stdio.h>
#include <string.h>

#include "util.h"

#ifdef STRLIB_NO_SHORT_NAMES
#undef STRLIB_NO_SHORT_NAMES
#endif
#define DEBUG

Test(util_tests, fx_memmem_find_substr) {
    // setup
    const char* hay = "Hello World!";
    size_t hlen = strlen(hay);
    const char* needle = "World";
    size_t nlen = strlen(needle);
    int expect_needle_start = strlen("Hello ");

    // test
    char* actual = (char*)fx_memmem(hay, hlen, needle, nlen);

    // validate
    cr_expect(actual - hay == expect_needle_start, "Expected actual - hay == expect_needle_start");
    cr_expect((strncmp(actual, needle, nlen) == 0),
              "Expected (strncmp(actual, needle, nlen) == 0)");
    cr_expect((strncmp(actual, hay + expect_needle_start, nlen) == 0),
              "Expected (strncmp(actual, hay[expect_needle_start], nlen) == 0)");
}

Test(util_tests, fx_memmem_retrun_null_if_not_found) {
    // setup
    const char* hay = "Hello World!";
    size_t hlen = strlen(hay);
    const char* needle = "foo";
    size_t nlen = strlen(needle);

    // test
    char* actual = (char*)fx_memmem(hay, hlen, needle, nlen);
    cr_expect(actual == NULL, "Expect actual == NULL");
}