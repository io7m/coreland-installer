#include "fmt.h"

unsigned int fmt_uint(char *s, unsigned int ui)
{
  return fmt_ulong(s, (unsigned long) ui);
}

