#include "install.h"

#if INSTALL_OS_TYPE == INSTALL_OS_POSIX

#include <grp.h>
#include <pwd.h>
#include <unistd.h>

static int
lookup_uid (const char *user, int *uid)
{
  struct passwd *pwd;

  pwd = getpwnam(user);
  if (!pwd) return 0;

  *uid = pwd->pw_uid;
  return 1;
}

static int
lookup_gid (const char *group, int *gid)
{
  struct group *grp;

  grp = getgrnam(group);
  if (!grp) return 0;

  *gid = grp->gr_gid;
  return 1;
}

int
iposix_uidgid_lookup (const char *owner, const char *group, int *uid, int *gid)
{
  if (owner) if (!lookup_uid (owner, uid)) return 0;
  if (group) if (!lookup_gid (group, gid)) return 0;
  return 1;
}

void
iposix_uidgid_current (int *uid, int *gid)
{
  *uid = getuid ();
  *gid = getgid ();
}

int
iposix_file_set_ownership (const char *file, int uid, int gid)
{
  if (chown (file, uid, gid) == -1) return -1;
  return 0;
}

int
iposix_install_init (void)
{
  return 1;
}

#endif
