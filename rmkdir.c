#include <sys/types.h>
#include <sys/stat.h>
#include "bin.h"
#include "error.h"
#include "rmkdir.h"
#include "str.h"

int rmkdir(const char *path, unsigned int mode)
{
  char pbuf[1024];
  const char *ptr;
  unsigned int len;
  unsigned int buflen;
  unsigned int bufpos;
  int pos;

  ptr = path;
  len = str_len(path);
  buflen = 1024;
  bufpos = 0;
  if (len >= 1024) return -1;

  for (;;) {
    if (!len) break;
    pos = str_chr(ptr, '/');
    if (pos == -1) pos = len;
    if (buflen <= (unsigned int) pos + 1) break;
    bin_copy(ptr, pbuf + bufpos, pos);
    bufpos += pos;
    buflen -= pos;
    pbuf[bufpos] = '/';
    ++bufpos;
    --buflen;
    pbuf[bufpos] = 0;
    if (mkdir(pbuf, mode) == -1)
      if (errno != error_exist && errno != error_isdir) return -1;
    ptr += pos;
    len -= pos;
    if (len) {
      ++ptr;
      --len;
      if (!len) break;
    }
  }

  return 0;
}
