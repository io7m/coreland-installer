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

unsigned int fmt_ulongx(char *s, unsigned long ul)
{
  unsigned long len; 
  unsigned long q;
  unsigned char c;
  len = 1; q = ul;
  
  /* number of digits */
  while (q > 15) { ++len; q /= 16; }
  
  /* digits -> ascii base16 */
  if (s) {
    s += len;
    do { 
      c = '0' + (ul & 15);
      if (c > '0' + 9) c += 'a' - '0' - 10;
      *--s = c;
      ul /= 16;
    } while (ul);
  }
  return len;
}

unsigned int fmt_ulongo(char *s, unsigned long ul)
{
  unsigned long len; 
  unsigned long q;
  len = 1; q = ul;
  
  /* no. digits */
  while (q > 7) { ++len; q >>= 3; }
  
  /* digit -> ascii (base10) */
  if (s) {
    s += len;
    do { *--s = '0' + (ul & 7); ul >>= 3; } while (ul);
  }
  return len;
}
