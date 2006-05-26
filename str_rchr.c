#include "str.h"

/*
 returns index of last occuring c or -1 if none
 */

int str_rchr(register const char *s, register int c)
{
  register const char *t;
  register const char *u;
  register char cc;
  int f = 0;
  for (t = s, cc = c, u = 0;;) {
    if (!*t) break; if (*t == cc) { u = t; f = 1; } ++t;
    if (!*t) break; if (*t == cc) { u = t; f = 1; } ++t;
    if (!*t) break; if (*t == cc) { u = t; f = 1; } ++t;
    if (!*t) break; if (*t == cc) { u = t; f = 1; } ++t;
  }
  if (f == 0) return -1;
  if (!u) u = t;
  return u - s;
}
