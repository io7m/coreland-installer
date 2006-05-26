#include "str.h"

/*
 returns > 0 if s > t
 returns < 0 if s < t
 returns 0 if s == t
*/

signed int str_diff(register const char *s, 
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

/*
 returns 1 if s == t
 returns 0 if s != t
*/

/*
unsigned int str_same(register const char *s,
                      register const char *t)
{
  return (str_diff(s, t) == 0);
}
*/
