#include "install.h"

#include <errno.h>
#include <stdio.h>
#include <string.h>

#if INSTALL_OS_TYPE == INSTALL_OS_POSIX
#include <sys/stat.h>
#include <unistd.h>
#endif

#if INSTALL_OS_TYPE == INSTALL_OS_WIN32
#include <io.h>
#endif

#define COPYBUF_SIZE 8192

char copybuf[COPYBUF_SIZE];
char tmpdst[INSTALL_MAX_PATHLEN];
char *src;
char *dst;
int uid;
int gid;
unsigned int perm;

void
complain (const char *s)
{
  if (s)
    printf ("error: %s: %s\n", s, install_error (errno));
  else
    printf ("error: %s\n", install_error (errno));
}

void
say (void)
{
  int t_uid = -1;
  int t_gid = -1;

#if INSTALL_OS_TYPE == INSTALL_OS_POSIX
  iposix_uidgid_current (&t_uid, &t_gid);
#endif
#if INSTALL_OS_TYPE == INSTALL_OS_WIN32
  iwin32_uidgid_current (&t_uid, &t_gid);
#endif

  if (uid != -1) t_uid = uid;
  if (gid != -1) t_gid = gid;

  printf("copy %s %s %d:%d %o\n", src, dst, t_uid, t_gid, perm);
  fflush(0);
}

int
copy (void)
{
  FILE *fd_src;
  FILE *fd_dst;
  size_t r;
  size_t w;
  int code;

  if (snprintf (tmpdst, 1024, "%s.tmp", dst) < 0) return 112;

  fd_src = fopen (src, "rb");
  if (fd_src == NULL) { complain ("fopen"); return 113; }
  fd_dst = fopen (tmpdst, "wb");
  if (fd_dst == NULL) { complain ("fopen"); code = 114; goto ERR; }

  for (;;) {
    r = fread (copybuf, 1, COPYBUF_SIZE, fd_src);
    if (r < COPYBUF_SIZE) {
      if (feof (fd_src)) break;
      if (ferror (fd_src)) {
        complain ("fread"); code = 115; goto ERR;
      }
    }
    while (r) {
      w = fwrite (copybuf, 1, COPYBUF_SIZE, fd_dst);
      if (w < COPYBUF_SIZE) {
        if (feof (fd_src)) break;
        if (ferror (fd_src)) {
          complain ("fwrite"); code = 116; goto ERR;
        }
      }
      r -= w;
    }
  }

  if (fflush (fd_dst) != 0) { complain ("fsync"); code = 117; goto ERR; }

  /* posix */
  if (chmod (tmpdst, perm) == -1) { complain ("chmod"); code = 118; goto ERR; }

#if INSTALL_OS_TYPE == INSTALL_OS_POSIX
  if (iposix_file_set_ownership (tmpdst, uid, gid) == -1) {
    complain ("set_ownership"); code = 119; goto ERR;
  }
#endif

#if INSTALL_OS_TYPE == INSTALL_OS_WIN32
  if (iwin32_file_set_ownership (tmpdst, uid, gid) == -1) {
    complain ("set_ownership"); code = 119; goto ERR;
  }
#endif

  if (rename (tmpdst, dst) == -1) { complain ("rename"); code = 120; goto ERR; }

  if (fclose (fd_dst) == -1) complain ("close");
  if (fclose (fd_src) == -1) complain ("close");
  return 0;
  ERR:
  if (unlink (tmpdst) == -1) complain ("unlink");
  return code;
}

int
main (int argc, char *argv[])
{
  --argc;
  ++argv;

  if (argc < 5) return 111;

  src = argv[0];
  dst = argv[1];
  if (!sscanf (argv[2], "%d", &uid)) return 111;
  if (!sscanf (argv[3], "%d", &gid)) return 111;
  if (!sscanf (argv[4], "%o", &perm)) return 111;

  say ();

  if (argc < 6) return copy ();
  return 0;
}
