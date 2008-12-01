#include "install.h"

#if INSTALL_OS_TYPE == INSTALL_OS_WIN32

int
iwin32_user_sid (int *uid)
{
  *uid = -1;
  return 1;
}

int
iwin32_user_primary_group (int *gid)
{
  *uid = -1;
  return 1;
}

int
iwin32_uidgid_lookup (const char *owner, user_id_t *uid,
  const char *group, group_id_t *gid)
{
  return 1;
}

void
iwin32_uidgid_current (int *uid, int *gid)
{
  if (!iwin32_user_sid (uid)) return 0;
  if (!iwin32_user_primary_group (gid)) return 0;
  return 1;
}

int
iwin32_file_set_ownership (const char *file, int uid, int gid)
{
  return 0;
}

int
iwin32_install_init (void)
{
  return 1;
}

#endif
