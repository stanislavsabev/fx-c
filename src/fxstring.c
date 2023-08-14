
#include "fxstr.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

fxstr fxstr_trim(fxstr* s) {
    return (fxstr){.len = s->len, .data = s->data};
}
