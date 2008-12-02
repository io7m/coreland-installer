#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "install.h"

char *dir;
char *user_name = INSTALL_NULL_USER_NAME;
char *group_name = INSTALL_NULL_GROUP_NAME;
user_id_t uid = INSTALL_NULL_UID;
group_id_t gid = INSTALL_NULL_GID;
unsigned int perm;

void
die (void)
{
  printf("failed: %s\n", install_error (errno));
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
  printf ("mkdir %s %s %s %o\n", dir, user_name, group_name, perm);
  fflush (0);
}

int
rmkdir (void)
{
  char pbuf[INSTALL_MAX_PATHLEN];
  unsigned int len;
  unsigned int pos;
  unsigned int buflen;
  unsigned int bufpos;
  int end;
  char *ptr;
  char *ptr2;

  buflen = INSTALL_MAX_PATHLEN;
  bufpos = 0;
  end = 0;
  len = strlen(dir);
  ptr = dir;

  if (len >= INSTALL_MAX_PATHLEN) return 113;

  for (;;) {
    if (!len) break;
    ptr2 = strchr (ptr, '/');
    if (!ptr2) {
      pos = len;
      end = 1;
    } else pos = ptr2 - ptr;
    if (buflen <= (unsigned int) pos + 1) break;
    memcpy (pbuf + bufpos, ptr, pos);
    bufpos += pos;
    buflen -= pos;
    pbuf[bufpos] = '/';
    ++bufpos;
    --buflen;
    pbuf[bufpos] = 0;
    if (install_mkdir (pbuf, perm) == -1) {
      if (!end) {
        if (errno != EEXIST && errno != EISDIR) die();
      } else die();
    }
    ptr += pos;
    len -= pos;
    if (len) {
      ++ptr;
      --len;
      if (!len) break;
    }
  }

  if (!install_file_set_ownership (pbuf, uid, gid)) die();
  return 0;
}

int
main (int argc, char *argv[])
{
  --argc;
  ++argv;

  if (argc < 4) return 111;

  dir = argv[0];
  user_name = argv[1];
  group_name = argv[2];
  if (!sscanf (argv[3], "%o", &perm)) return 111;

  say ();
  lookup ();

  if (argc < 5) return rmkdir ();
  return 0;
}
