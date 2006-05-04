#include "bin.h"

/* copy n bytes from ss to ds  */

void bin_copyr(register char *to, register const char *from,
               register unsigned int n)
{
  to += n;
  from += n;
  for (;;) {
    if (!n) return; *--to = *--from; --n;
    if (!n) return; *--to = *--from; --n;
    if (!n) return; *--to = *--from; --n;
    if (!n) return; *--to = *--from; --n;
  }
}
