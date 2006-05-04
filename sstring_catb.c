#include "sstring.h"

/* concat s ss->s
   returns new length of string
 */

unsigned int sstring_catb(sstring *ss, const char *s, unsigned int len)
{
  register unsigned int n;
  register char* ssp;
  n = len; ssp = ss->s;
  
  if (ss->len == ss->a) return 0;
  if ((ss->len + n) > ss->a) n = ss->a - ss->len; /* refuse overflow */
  ssp += ss->len;
  for (;;) {
    if (!n) break; *ssp++ = *s++; --n;
    if (!n) break; *ssp++ = *s++; --n;
    if (!n) break; *ssp++ = *s++; --n;
    if (!n) break; *ssp++ = *s++; --n;
  }
  return ss->len = ssp - ss->s;
}
