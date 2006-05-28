#include "fmt.h"

unsigned int fmt_uinto(char *s, unsigned int uio)
{
  return fmt_ulongo(s, (unsigned long) uio);
}

