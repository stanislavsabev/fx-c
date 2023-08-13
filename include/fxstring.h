#if !defined(FX_FXSTRING_H_)
#define FX_FXSTRING_H_

#include <stdlib.h>

///
#define FXSTR_REPT_LITERAL0(X)
#define FXSTR_REPT_LITERAL1(X) X
#define FXSTR_REPT_LITERAL2(X) FXSTR_REPT_LITERAL1(X) X
#define FXSTR_REPT_LITERAL3(X) FXSTR_REPT_LITERAL2(X) X
#define FXSTR_REPT_LITERAL4(X) FXSTR_REPT_LITERAL3(X) X
#define FXSTR_REPT_LITERAL5(X) FXSTR_REPT_LITERAL4(X) X
#define FXSTR_REPT_LITERAL6(X) FXSTR_REPT_LITERAL5(X) X
#define FXSTR_REPT_LITERAL7(X) FXSTR_REPT_LITERAL6(X) X
#define FXSTR_REPT_LITERAL8(X) FXSTR_REPT_LITERAL7(X) X
#define FXSTR_REPT_LITERAL9(X) FXSTR_REPT_LITERAL8(X) X
#define FXSTR_REPT_LITERAL10(X) FXSTR_REPT_LITERAL9(X) X

#define FXSTR_REPT_LITERAL(HUNDREDS, TENS, ONES, X)                             \
    FXSTR_REPT_LITERAL##HUNDREDS(FXSTR_REPT_LITERAL10(FXSTR_REPT_LITERAL10(X))) \
        FXSTR_REPT_LITERAL##TENS(FXSTR_REPT_LITERAL10(X)) FXSTR_REPT_LITERAL##ONES(X)

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
