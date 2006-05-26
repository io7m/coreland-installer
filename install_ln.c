#include "close.h"
#include "install.h"
#include "open.h"
#include "read.h"
#include "str.h"
#include "sstring.h"
#include "syserr.h"

/* basic understanding of virtual libs */

int install_libname(sstring *sstr)
{
  char *s;
  char buf[32];
  int n;
  int r;
  int fd;
  int ret;
  int clean;

  ret = 1;
  n = str_rchr(sstr->s, '.');
  if (n == -1) return 0;
  fd = open_ro(sstr->s);
  if (fd == -1) return 0;
  r = read(fd, buf, 32);
  if (r == 0) { ret = 0; goto END; }
  if (r == -1) {
    syserr_warn1sys("error: open: "); ret = 0; goto END;
  }
  s = buf;
  clean = 0;
  while (r) {
    switch (*s) {
      case ' ':
      case '\t':
      case '\n':
        s[0] = 0;
        clean = 1;
        break;
      default:
        break;
    }
    if (clean) break;
    --r; ++s;
  }
  sstring_trunc(sstr);
  sstring_cats(sstr, buf);
  sstring_0(sstr);

  END:
  if (close(fd) == -1) syserr_warn1sys("error: close: ");
  return ret;
}
