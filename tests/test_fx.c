#define FX_IMPLEMENTATION
#include "fx.h"

#include <criterion/criterion.h>

// Test(String_tests, String_null_create) {
//     // test
//     String actual = String_null();

//     // validate
//     cr_expect(actual.data == NULL, "Expected actual.data == NULL");
//     cr_expect(actual.len == 0, "Expected actual.len == 0");
//     cr_expect(actual.capacity == 0, "Expected actual.capacity == 0");
// }

Test(fx_tests, test_mem_is_power_of_two) {
  b32 actual = mem_is_power_of_two(4);
  cr_expect(actual == true, "Expected true, 4 is power of two");
  actual = mem_is_power_of_two(5);
  cr_expect(actual == true, "Expected false, 5 is not power of two");
}

// Test(fx_tests, mem_align_forward) {
//     mem_align_forward();
// }

// Test(fx_tests, arena_init) {
//     arena_init();
// }

// Test(fx_tests, *arena_alloc_align) {
//     *arena_alloc_align();
// }

// Test(fx_tests, arena_free) {
//     arena_free();
// }

// Test(fx_tests, arena_reset) {
//     arena_reset();
// }

// Test(fx_tests, arena_snapshot_save) {
//     arena_snapshot_save();
// }

// Test(fx_tests, arena_snapshot_restore) {
//     arena_snapshot_restore();
// }
