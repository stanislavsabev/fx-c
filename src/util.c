#include "util.h"

#include <string.h>

/**
 * @brief Finds the start of the first occurrence of the substring 'needle' in 'hay'.
 * @param hay haystack to search
 * @param hlen haystack len
 * @param needle substr to find
 * @param nlen needle len
 * @returns pointer to the beginning of the sub-string, or NULL.
 */
void* fx_memmem(const void* hay, size_t hlen, const void* needle, size_t nlen) {
    register char *cur, *last;
    const char* cl = (const char*)hay;
    const char* cs = (const char*)needle;

    /* we need something to compare */
    if (hlen == 0 || nlen == 0) return NULL;

    /* "needle" must be smaller or equal to "hay" */
    if (hlen < nlen) return NULL;

    /* special case where nlen == 1 */
    if (nlen == 1) return memchr(hay, (int)*cs, hlen);

    /* the last position where its possible to find "needle" in "hay" */
    last = (char*)cl + hlen - nlen;

    for (cur = (char*)cl; cur <= last; cur++)
        if (cur[0] == cs[0] && memcmp(cur, cs, nlen) == 0) return cur;

    return NULL;
}
