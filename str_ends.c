#include "str.h"

int str_ends(const char *s, const char *end)
{
  register unsigned long slen;
  register unsigned long elen;
  slen = str_len(s);
  elen = str_len(end);
  if (elen > slen) elen = slen;
  s += (slen - elen);
  return str_same(s, end);
}
