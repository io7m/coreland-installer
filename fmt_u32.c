#include "fmt.h"

unsigned int fmt_u32(char *s, uint32 ul)
{
  return fmt_u64(s, (uint64) ul);
}
