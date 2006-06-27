#include "str.h"

int str_diff(register const char *s, 
             register const char *t)
{
  register char u;
  for (;;) {
    u = *s; if (u != *t) break; if (!u) break; ++s; ++t;
    u = *s; if (u != *t) break; if (!u) break; ++s; ++t;
    u = *s; if (u != *t) break; if (!u) break; ++s; ++t;
    u = *s; if (u != *t) break; if (!u) break; ++s; ++t;
  }
  return ((int)(unsigned int)(unsigned char) u) - 
         ((int)(unsigned int)(unsigned char) *t);
}
