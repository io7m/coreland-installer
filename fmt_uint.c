#include "fmt.h"

unsigned int fmt_uint(char *s, unsigned int ui)
{
  return fmt_ulong(s, (unsigned long) ui);
}

unsigned int fmt_uintx(char *s, unsigned int uix)
{
  return fmt_ulongx(s, (unsigned long) uix);
}

unsigned int fmt_uinto(char *s, unsigned int uio)
{
  return fmt_ulongo(s, (unsigned long) uio);
}
