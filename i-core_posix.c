#include "install.h"

#if INSTALL_OS_TYPE == INSTALL_OS_POSIX

#include <grp.h>
#include <pwd.h>
#include <unistd.h>

static int
lookup_uid (const char *user, user_id_t *uid)
{
  struct passwd *pwd;

  pwd = getpwnam(user);
  if (!pwd) return 0;

  uid->value = pwd->pw_uid;
  return 1;
}

static int
lookup_gid (const char *group, group_id_t *gid)
{
  struct group *grp;

  grp = getgrnam(group);
  if (!grp) return 0;

  gid->value = grp->gr_gid;
  return 1;
}

int
iposix_uidgid_lookup (const char *owner, user_id_t *uid,
  const char *group, group_id_t *gid)
{
  if (owner) if (!lookup_uid (owner, uid)) return 0;
  if (group) if (!lookup_gid (group, gid)) return 0;
  return 1;
}

void
iposix_uidgid_current (user_id_t *uid, group_id_t *gid)
{
  uid->value = getuid ();
  gid->value = getgid ();
}

int
iposix_file_set_ownership (const char *file, user_id_t uid, group_id_t gid)
{
  if (chown (file, uid.value, gid.value) == -1) return 0;
  return 1;
}

int
iposix_install_init (void)
{
  return 1;
}

#endif
