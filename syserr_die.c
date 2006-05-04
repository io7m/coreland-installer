#include "buffer.h"
#include "exit.h"
#include "syserr.h"

void syserr_warn(const char *x1, const char *x2, const char *x3, 
                 const char *x4, const char *x5, const char *x6,
                 struct syserr *se)
{
  syserr_init();
 
  if (x1) buffer_puts(buffer2, x1);
  if (x2) buffer_puts(buffer2, x2);
  if (x3) buffer_puts(buffer2, x3);
  if (x4) buffer_puts(buffer2, x4);
  if (x5) buffer_puts(buffer2, x5);
  if (x6) buffer_puts(buffer2, x6);
 
  while(se) {
    if (se->x) buffer_puts(buffer2, se->x);
    if (se->y) buffer_puts(buffer2, se->y);
    if (se->z) buffer_puts(buffer2, se->z);
    se = se->w;
  }
 
  buffer_puts(buffer2, "\n");
  buffer_flush(buffer2);
}

void syserr_die(int e, const char *x1, const char *x2, const char *x3, 
                       const char *x4, const char *x5, const char *x6,
                       struct syserr *se)
{
  syserr_warn(x1, x2, x3, x4, x5, x6, se);
  _exit(e);
}
