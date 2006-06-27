#include "str.h"

unsigned long str_len(const char *s)
{
  register const char* sc;
  for (sc = s;;) {
    if (!*sc) return sc - s; ++sc;
    if (!*sc) return sc - s; ++sc;
    if (!*sc) return sc - s; ++sc;
    if (!*sc) return sc - s; ++sc;
  }
}

