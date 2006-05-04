#include "sstring.h"

unsigned int sstring_chop(sstring *s, unsigned int len)
{
  char *str;

  if (len >= s->a) return s->a;

  str = s->s;
  str[len] = 0;
  s->len = len;

  return len;
}
