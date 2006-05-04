#include "fmt.h"
#include "uint64.h"

unsigned int fmt_u64o(char *s, uint64 ul)
{
  register uint64 l; 
  register uint64 q;
  l = 1; q = ul;
  
  /* no. digits */
  while (q > 7) { 
    ++l; 
    q >>= 3;
  }
  
  /* digit -> ascii (base10) */
  if (s) {
    s += l;
    do { 
      *--s = '0' + (ul & 7);
      ul >>= 3;
    } while (ul);
  }
  return l;
}
