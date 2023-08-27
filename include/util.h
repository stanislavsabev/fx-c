
#ifndef FX_FXUTIL_H_
#define FX_FXUTIL_H_

#include <string.h>
#include <stdbool.h>

#ifndef FX_NO_SHORT_NAMES

#define DEFINE_TRIVIAL_CLEANUP_FUNC           FX_DEFINE_TRIVIAL_CLEANUP_FUNC
#define yes_no(b)                             fx_yes_no(b)
#define true_false(b)                         fx_true_false(b)
#define one_zero(b)                           fx_one_zero(b)
#define rept_literal(hundreds, tens, ones, s) fx_rept_literal(hundreds, tens, ones, s)

#endif   // FX_NO_SHORT_NAMES

///@brief Gets the address pointing to the container which accommodates the respective member
///@param ptr a pointer to container (struct)
///@param type of the container
///@param the name of the member the pointer refers to
#define container_of(ptr, type, member)                    \
    ({                                                     \
        const typeof(((type *)0)->member) *__mptr = (ptr); \
        (type *)((char *)__mptr - offsetof(type, member)); \
    })

#define FX_DEFINE_TRIVIAL_CLEANUP_FUNC(type, func) \
    static inline void func##p(type *p) {          \
        if (*p) func(*p);                          \
    }                                              \
    struct __useless_struct_to_allow_trailing_semicolon__

#define fx_rept_literal0(s)
#define fx_rept_literal1(s)  s
#define fx_rept_literal2(s)  fx_rept_literal1(s) s
#define fx_rept_literal3(s)  fx_rept_literal2(s) s
#define fx_rept_literal4(s)  fx_rept_literal3(s) s
#define fx_rept_literal5(s)  fx_rept_literal4(s) s
#define fx_rept_literal6(s)  fx_rept_literal5(s) s
#define fx_rept_literal7(s)  fx_rept_literal6(s) s
#define fx_rept_literal8(s)  fx_rept_literal7(s) s
#define fx_rept_literal9(s)  fx_rept_literal8(s) s
#define fx_rept_literal10(s) fx_rept_literal9(s) s

/**
 * @brief Repeat string literal
 * @param hundreds number from 0 to 10
 * @param tens number from 0 to 10
 * @param ones number from 0 to 10
 * @param s string to repeat
 * @returns repeated string literal
 */
#define fx_rept_literal(hundreds, tens, ones, s)                       \
    fx_rept_literal##hundreds(fx_rept_literal10(fx_rept_literal10(s))) \
        fx_rept_literal##tens(fx_rept_literal10(s)) fx_rept_literal##ones(s)

#ifdef DEBUG
#define dprintf(__format, ...)                  \
    do {                                        \
        fprintf(stderr, __format, __VA_ARGS__); \
    } while (false)

#define dfprintf(__stream, __format, ...)         \
    do {                                          \
        fprintf(__stream, __format, __VA_ARGS__); \
    } while (false)
#else
#define dprintf(...) \
    do {             \
    } while (false)

#define dfprintf(...) \
    do {              \
    } while (false)
#endif

static inline const char *fx_yes_no(bool b) {
    return b ? "yes" : "no";
}

static inline const char *fx_true_false(bool b) {
    return b ? "true" : "false";
}

static inline const char *fx_one_zero(bool b) {
    return b ? "1" : "0";
}

/**
 * @brief Finds the start of the first occurrence of the substring 'needle' in 'hay'.
 * @param hay haystack to search
 * @param hlen haystack len
 * @param needle substr to find
 * @param nlen needle len
 * @returns pointer to the beginning of the sub-string, or NULL.
 */
void *fx_memmem(const void *hay, size_t hlen, const void *needle, size_t nlen) {
    register char *cur, *last;
    const char *cl = (const char *)hay;
    const char *cs = (const char *)needle;

    /* we need something to compare */
    if (hlen == 0 || nlen == 0) return NULL;

    /* "needle" must be smaller or equal to "hay" */
    if (hlen < nlen) return NULL;

    /* special case where nlen == 1 */
    if (nlen == 1) return memchr(hay, (int)*cs, hlen);

    /* the last position where its possible to find "needle" in "hay" */
    last = (char *)cl + hlen - nlen;

    for (cur = (char *)cl; cur <= last; cur++)
        if (cur[0] == cs[0] && memcmp(cur, cs, nlen) == 0) return cur;

    return NULL;
}

#endif   // FX_FXUTIL_H_