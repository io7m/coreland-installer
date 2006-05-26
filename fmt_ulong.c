#include "fmt.h"

unsigned int fmt_ulong(char *s, unsigned long ul)
{
  unsigned int len;
  unsigned long q;
  len = 1; q = ul;

  /* number of digits */
  while (q > 9) { ++len; q /= 10; }

  /* digits -> ascii base16 */
  if (s) {
    s += len;
    do { *--s = '0' + (ul % 10); ul /= 10; } while(ul);
  }
  return len;
}

