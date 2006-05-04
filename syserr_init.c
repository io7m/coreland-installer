#include "error.h"
#include "syserr.h"

struct syserr syserr_sys;

void syserr_init(void)
{
  syserr_sys.w = 0;
  syserr_sys.x = error_str(errno);
  syserr_sys.y = "";
  syserr_sys.z = "";
}
