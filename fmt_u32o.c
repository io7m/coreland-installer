#include "fmt.h"

unsigned int fmt_u32o(char *s, uint32 ul)
{
  return fmt_u64o(s, (uint64) ul);
}
