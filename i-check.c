#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "install.h"

char *src_file;
char *dst_file;
char *type_name;
char *user_name;
char *group_name;
user_id_t uid = INSTALL_NULL_UID;
group_id_t gid = INSTALL_NULL_GID;
enum install_file_type_t type;
unsigned int perm;
unsigned long size_want;

void
complain (const char *s)
{
  if (s)
    printf("failed: %s: %s\n", s, install_error (errno));
  else
    printf("failed: %s\n", install_error (errno));
}

void
die (void)
{
  printf ("failed: %s\n", install_error (errno));
  fflush (0);
  exit (112);
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
  printf ("check %s %s %s %s %o %s %lu\n", src_file, dst_file, user_name,
    group_name, perm, type_name, size_want);

  fflush (0);
}

int
check (void)
{
  char uid_want_str[INSTALL_FMT_UID];
  char uid_got_str[INSTALL_FMT_UID];
  char gid_want_str[INSTALL_FMT_GID];
  char gid_got_str[INSTALL_FMT_GID];
  user_id_t got_uid;
  group_id_t got_gid;
  enum install_file_type_t got_type;
  unsigned int got_mode;
  unsigned int want_mode;
  const char *got_type_name;
  unsigned long size_got;
  int no_follow;

  /* check file type */
  no_follow = (type == INSTALL_FILE_TYPE_SYMLINK) ? 1 : 0;
  if (!install_file_type (dst_file, &got_type, no_follow)) die ();
  if (!install_file_type_name_lookup (got_type, &got_type_name)) {
    printf ("failed: unknown filetype\n");
    return 1;
  }
  if (type != got_type) {
    printf ("failed: filetype %s not %s\n", got_type_name, type_name);
    return 1;
  }

  /* check file size */
  if (type == INSTALL_FILE_TYPE_FILE) {
    if (!install_file_size (dst_file, &size_got)) die ();
    if (size_want != size_got) {
      printf ("failed: size %lu not %lu\n", size_got, size_want);
      return 1;
    }
  }

  /* check file permissions */
  if (!install_file_get_mode (dst_file, &got_mode)) die ();
  got_mode = got_mode & 0755;
  want_mode = perm;
  if (got_mode != want_mode) {
    printf ("failed: mode %o not %o\n", got_mode, want_mode);
    return 1;
  }
 
  /* check file ownership */
  if (!install_file_get_ownership (dst_file, &got_uid, &got_gid)) die ();
  uid_want_str [install_fmt_uid (uid_want_str, uid)] = 0;
  gid_want_str [install_fmt_gid (gid_want_str, gid)] = 0;
  uid_got_str [install_fmt_uid (uid_got_str, uid)] = 0;
  gid_got_str [install_fmt_gid (gid_got_str, gid)] = 0;

  if (!install_compare_uid (uid, got_uid)) {
    printf ("failed: uid %s not %s\n", uid_got_str, uid_want_str);
    return 1;
  }
  if (!install_compare_gid (gid, got_gid)) {
    printf ("failed: gid %s not %s\n", gid_got_str, gid_want_str);
    return 1;
  }

  return 0;
}

int
main (int argc, char *argv[])
{
  --argc;
  ++argv;

  if (argc < 6) return 111;

  src_file = argv[0];
  dst_file = argv[1];
  user_name = argv[2];
  group_name = argv[3];
  if (!sscanf(argv[4], "%o", &perm)) return 111;
  type_name = argv[5];

  install_file_size (src_file, &size_want);
  if (!install_file_type_lookup (type_name, &type)) return 111;

  say ();
  lookup ();

  if (argc < 7) return check ();
  return 0;
}
