#include "install.h"

#if INSTALL_OS_TYPE == INSTALL_OS_WIN32

static int
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

static int
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
iwin32_compare_gid (group_id_t a, group_id_t b)
{
  return EqualSid (a.value, b.value);
}

int
iwin32_compare_uid (user_id_t a, user_id_t b)
{
  return EqualSid (a.value, b.value);
}

int
iwin32_gid_current (group_id_t *gid)
{
  return iwin32_user_primary_group (gid);
}

int
iwin32_gid_lookup (const char *name, group_id_t *gid)
{
  return 0;
}

int
iwin32_uid_current (user_id_t *uid)
{
  return iwin32_user_sid (uid);
}

int
iwin32_uid_lookup (const char *name, user_id_t *uid)
{
  return 0;
}

int
iwin32_file_set_ownership (const char *file, user_id_t uid, group_id_t gid)
{
  return 0;
}

int
iwin32_file_get_ownership (const char *file, user_id_t *uid, group_id_t *gid)
{
  return 0;
}

int
iwin32_file_link (const char *src, const char *dst)
{
  user_id_t uid;
  group_id_t gid;
  unsigned int mode;

  fprintf (stderr, "warn: filesystem does not support symlinks, copying...\n");

  /* only vista supports symlinks */
  if (!iwin32_file_get_ownership (src, &uid, &gid)) return 0;
  if (!iwin32_file_get_mode (src, &mode)) return 0;
  return install_file_copy (src, dst, uid, gid, mode);
}

int
iwin32_install_init (void)
{
  return 1;
}

unsigned int
iwin32_fmt_gid (char *buffer, group_id_t gid)
{
  const char *sid_str;
  if (!ConvertSidToStringSid (gid.value, &sid_str)) return 0;
  memcpy (buffer, sid_str, strlen (sid_str));
  LocalFree (sid_str);
  return 1;
}

unsigned int
iwin32_fmt_uid (char *, user_id_t)
{
  const char *sid_str;
  if (!ConvertSidToStringSid (gid.value, &sid_str)) return 0;
  memcpy (buffer, sid_str, strlen (sid_str));
  LocalFree (sid_str);
  return 1;
}

unsigned int
iwin32_scan_gid (const char *buffer, group_id_t *gid)
{
  if (!ConvertStringSidToSid (buffer, &gid->value)) return 0;
  return strlen (buffer);
}

unsigned int
iwin32_scan_uid (const char *buffer, user_id_t *uid)
{
  if (!ConvertStringSidToSid (buffer, &gid->value)) return 0;
  return strlen (buffer);
}

#endif