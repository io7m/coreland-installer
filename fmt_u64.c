#include "fmt.h"
#include "uint64.h"

unsigned int fmt_u64(char *s, uint64 ul)
{
  register uint64 l; 
  register uint64 q;
  l = 1; q = ul;
  
  /* no. digits */
  while (q > 9) { 
    ++l; 
    q /= 10;
  }
  
  /* digit -> ascii (base10) */
  if (s) {
    s += l;
    do { 
      *--s = '0' + (ul % 10);
      ul /= 10;
    } while (ul);
  }
  return l;
}
