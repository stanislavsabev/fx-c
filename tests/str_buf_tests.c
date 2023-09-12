#include <criterion/criterion.h>
#include <string.h>

#include "str.h"
#include "util.h"

#ifdef FX_NO_SHORT_NAMES
#undef FX_NO_SHORT_NAMES
#endif

Test(str_buf_tests, fxstr_buf_null_create) {
    str_buf_t nulstr = fxstr_buf_null();

    cr_expect(nulstr.data == NULL, "Expected nulstr.data == NULL");
    cr_expect(nulstr.len == 0, "Expected nulstr.len == 0");
    cr_expect(nulstr.capacity == 0, "Expected nulstr.capacity == 0");
}