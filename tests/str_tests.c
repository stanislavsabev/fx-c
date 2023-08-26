#include <criterion/criterion.h>

#include "str.h"

Test( fxstrtests, create_null_str ) {
    fxstr_t nulstr = fxstr_null();

    cr_expect(nulstr.data == NULL, "Expected fxstr.data == NULL");
    cr_expect(nulstr.len == 0, "Expected fxstr.len == 0");
}