#include "sstring.h"

unsigned int sstring_cats(sstring *ss, const char *s)
{
  register const char* t;
  for (t = s;;) {
    if (!*t) return sstring_catb(ss, s, t-s); ++t;
    if (!*t) return sstring_catb(ss, s, t-s); ++t;
    if (!*t) return sstring_catb(ss, s, t-s); ++t;
    if (!*t) return sstring_catb(ss, s, t-s); ++t;
  }
}
