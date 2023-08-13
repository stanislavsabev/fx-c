#if !defined(FX_FXSTRING_H_)
#define FX_FXSTRING_H_

#include <stdbool.h>
#include <stdlib.h>

///
#define fxstr_rept_lit0(s)
#define fxstr_rept_lit1(s) s
#define fxstr_rept_lit2(s) fxstr_rept_lit1(s) s
#define fxstr_rept_lit3(s) fxstr_rept_lit2(s) s
#define fxstr_rept_lit4(s) fxstr_rept_lit3(s) s
#define fxstr_rept_lit5(s) fxstr_rept_lit4(s) s
#define fxstr_rept_lit6(s) fxstr_rept_lit5(s) s
#define fxstr_rept_lit7(s) fxstr_rept_lit6(s) s
#define fxstr_rept_lit8(s) fxstr_rept_lit7(s) s
#define fxstr_rept_lit9(s) fxstr_rept_lit8(s) s
#define fxstr_rept_lit10(s) fxstr_rept_lit9(s) s

/**
 * @brief Repeat string literal
 * @param hundreds number from 0 to 10
 * @param tens number from 0 to 10
 * @param ones number from 0 to 10
 * @param s string to repeat
 * @returns repeated string literal
 */
#define fxstr_rept_lit(hundreds, tens, ones, s)                             \
    fxstr_rept_lit##hundreds(fxstr_rept_lit10(fxstr_rept_lit10(s))) \
        fxstr_rept_lit##tens(fxstr_rept_lit10(s)) fxstr_rept_lit##ones(s)

static inline char* bool_to_str(bool iso) {
    return iso ? "true" : "false";
}

/**
 * @brief Fx string - struct with <string> and <len>.
 */
typedef struct FxStr {
    size_t len;
    char* s;
} FxStr;

/**
 * @brief Trims string <s> and writes the result onto <trimmed>.
 * @param s string to trim
 * @param trimmed buffer with at least len size, to hold the result
 * @returns number of characters trimmed
 */
int fxstr_trim(FxStr* s, FxStr* trimmed);

#endif   // FX_FXSTRING_H_
