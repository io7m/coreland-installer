#include "install.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if INSTALL_OS_TYPE == INSTALL_OS_POSIX
#include <sys/stat.h>
#include <unistd.h>
#endif

#if INSTALL_OS_TYPE == INSTALL_OS_WIN32
#include <io.h>
#endif

#define COPYBUF_SIZE 8192

char *user_name;
char *group_name;
char *src;
char *dst;
user_id_t uid = INSTALL_NULL_UID;
group_id_t gid = INSTALL_NULL_GID;
unsigned int perm;
unsigned long size;

void
die (void)
{
  printf ("failed: %s\n", install_error (errno));
  fflush (0);
  exit (112);
}

void
complain (const char *s)
{
  if (s)
    printf ("error: %s: %s\n", s, install_error (errno));
  else
    printf ("error: %s\n", install_error (errno));
}

void
lookup (void)
{
  if (strcmp (user_name, ":") == 0) {
    if (!install_uid_current (&uid)) die();
  } else {
    if (!install_uid_lookup (user_name, &uid)) die();
  }

  if (strcmp (group_name, ":") == 0) {
    if (!install_gid_current (&gid)) die();
  } else {
    if (!install_gid_lookup (user_name, &gid)) die();
  }
}

void
say (void)
{
  printf("copy %s %s %s %s %o %lu\n", src, dst, user_name, group_name, perm,
    size);
  fflush(0);
}

int
main (int argc, char *argv[])
{
  --argc;
  ++argv;

  if (argc < 5) return 111;

  src = argv[0];
  dst = argv[1];
  user_name = argv[2];
  group_name = argv[3];
  if (!sscanf (argv[4], "%o", &perm)) return 111;

  install_file_size (src, &size);

  say ();
  lookup ();

  if (argc < 6)
    if (!install_file_copy (src, dst, uid, gid, perm))
      die();

  return 0;
}
