#include "open.h"

int open_trunc(const char *f)
{
  return open(f, O_WRONLY | O_TRUNC | O_CREAT | O_NONBLOCK, 0600);
}
