#include "str.h"

/* 1 if s finishes with ends, 0 if it doesn't */

int str_ends(const char *s, const char *end)
{
  register unsigned int slen;
  register unsigned int elen;
  slen = str_len(s);
  elen = str_len(end);
  if (elen > slen) elen = slen;
  s += (slen - elen);
  return str_same(s, end);
}
