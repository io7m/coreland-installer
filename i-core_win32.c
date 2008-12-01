#include "install.h"

#if INSTALL_OS_TYPE == INSTALL_OS_WIN32

int
iwin32_user_sid (user_id_t *uid)
{
  HANDLE thread_tok;
  DWORD needed;
  TOKEN_USER *user;
 
  if (!OpenProcessToken (GetCurrentProcess(),
    STANDARD_RIGHTS_READ | READ_CONTROL | TOKEN_QUERY, &thread_tok)) return 0;

  if (!GetTokenInformation (thread_tok, TokenUser, NULL, 0, &needed)) {
    if (!GetLastError () == ERROR_INSUFFICIENT_BUFFER) {
      user = malloc (needed);
      if (!user) return 0;
      if (GetTokenInformation (thread_tok, TokenUser, user, needed, &needed)) {
        *uid = user->User.Sid;
      }
      free (user);
    }
  }
  return 1;
}

int
iwin32_user_primary_group (group_id_t *gid)
{
  HANDLE thread_tok;
  DWORD needed;
  TOKEN_PRIMARY_GROUP *group;

  if (!OpenProcessToken (GetCurrentProcess(),
    STANDARD_RIGHTS_READ | READ_CONTROL | TOKEN_QUERY, &thread_tok)) return 0;

  if (!GetTokenInformation (thread_tok, TokenPrimaryGroup, NULL, 0, &needed)) {
    if (!GetLastError () == ERROR_INSUFFICIENT_BUFFER) {
      group = malloc (needed);
      if (!group) return 0;
      if (GetTokenInformation (thread_tok, TokenPrimaryGroup, group, needed, &needed)) {
        *gid = group->PrimaryGroup;
      }
      free (group);
    }
  }
  return 1;
}

int
iwin32_uidgid_lookup (const char *owner, user_id_t *uid,
  const char *group, group_id_t *gid)
{
  return 1;
}

int
iwin32_uidgid_current (user_id_t *uid, group_id_t *gid)
{
  if (!iwin32_user_sid (uid)) return 0;
  if (!iwin32_user_primary_group (gid)) return 0;
  return 1;
}

int
iwin32_file_set_ownership (const char *file, user_id_t uid, group_id_t gid)
{
  return 0;
}

int
iwin32_install_init (void)
{
  return 1;
}

unsigned int
iwin32_fmt_gid (char *buffer, group_id_t gid)
{
  return 0;
}

unsigned int
iwin32_fmt_uid (char *, user_id_t)
{
  return 0;
}

unsigned int
iwin32_scan_gid (const char *buffer, group_id_t *gid)
{
  return 0;
}

unsigned int
iwin32_scan_uid (const char *buffer, user_id_t *uid)
{
  return 0;
}

#endif
