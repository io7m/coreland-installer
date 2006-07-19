#include "str.h"

long str_chr(register const char *s, register int c)
{
  register const char* t;
  register char cc;
  for (t = s, cc = c;;) {
    if (!*t) return -1; if (*t == cc) return t - s; ++t;
    if (!*t) return -1; if (*t == cc) return t - s; ++t;
    if (!*t) return -1; if (*t == cc) return t - s; ++t;
    if (!*t) return -1; if (*t == cc) return t - s; ++t;
  }
}
