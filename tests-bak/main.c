#include <stdio.h>
#include <string.h>

#include "strlib.h"
#include "util.h"

int main() {
    // test
    const char* data = "abc";
    size_t ln = strlen(data);

    char* buff = malloc(ln);
    memcpy(buff, "abc", ln);

    String actual = String_acquire(&buff, ln);
    // validate
    // cr_expect(actual.len == expect_left_len, "Expected actual.len == expect_left_len");
    printf("actual: '%.*s', len: %lu\n", (int)actual.len, actual.data, actual.len);
    printf("buff: %p, actual %p, same = %s\n", buff, actual.data, true_false(actual.data == buff));

    // delete actual
    String_free(&actual);
    printf("buff is NULL: %s\n", true_false(buff == NULL));
    printf("actual is NULL: %s\n", true_false(String_is_null(&actual)));

    // printf("str: '%.*s', len: %lu\n", (int)str.len, str.data, str.len);
    // printf("is null: %s\n", true_false(is_null));
    // puts("done");
    // cr_expect(strncmp(actual.data, expect_left_data, expect_left_len) == 0,
    //           "Expected strncmp(actual.data, expect_left_data, expect_left_len) == 0");

    // cr_expect(str.len == expect_right_len, "Expected str.len == expect_right_len");

    // cr_expect(strncmp(str.data, expect_right_data, expect_right_len) == 0,
    //           "Expected strncmp(str.data, expect_right_data, expect_left_len) == 0");

    // cr_expect(actual.len + str.len == len - 1, "Expected actual.len + str.len == len - 1");
    return 0;
}
