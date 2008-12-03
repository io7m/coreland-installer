#include "install.h"

#if INSTALL_OS_TYPE == INSTALL_OS_WIN32

#include <windows.h>
#include <sddl.h>
#include <io.h>
#include <stdio.h>

static int
iwin32_user_sid (user_id_t *uid)
{
  char name [MAX_SIZE];
  char domain [MAX_SIZE];
  DWORD domain_size = MAX_SIZE;
  DWORD sid_size = MAX_SIZE;
  DWORD name_size = MAX_SIZE;
  SID *sid;
  SID_NAME_USE account_type;

  if (!GetUserName (name, &name_size)) return 0;
  
  sid = malloc (MAX_SIZE);
  if (!LookupAccountName (NULL, name, sid, &sid_size,
    domain, &domain_size, &account_type)) return 0;

  uid->value = sid;
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
        gid->value = group->PrimaryGroup;
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
iwin32_file_get_mode (const char *file, unsigned int *mode)
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

struct install_status_t
iwin32_install_init (void)
{
  struct install_status_t status;
  status.status = INSTALL_STATUS_OK;

  memcpy (exec_suffix, ".exe", 4);
  return status; 
}

unsigned int
iwin32_fmt_gid (char *buffer, group_id_t gid)
{
  char *sid_str;
  if (!ConvertSidToStringSid (gid.value, &sid_str)) return 0;
  memcpy (buffer, sid_str, strlen (sid_str));
  LocalFree (sid_str);
  return 1;
}

unsigned int
iwin32_fmt_uid (char *buffer, user_id_t uid)
{
  char *sid_str;
  if (!ConvertSidToStringSid (uid.value, &sid_str)) return 0;
  memcpy (buffer, sid_str, strlen (sid_str));
  LocalFree (sid_str);
  return 1;
}

unsigned int
iwin32_scan_gid (const char *buffer, group_id_t *gid)
{
  if (!ConvertStringSidToSid ((char *) buffer, &gid->value)) return 0;
  return strlen (buffer);
}

unsigned int
iwin32_scan_uid (const char *buffer, user_id_t *uid)
{
  if (!ConvertStringSidToSid ((char *) buffer, &uid->value)) return 0;
  return strlen (buffer);
}

unsigned int
iwin32_umask (unsigned int m)
{
  return m;
}

int
iwin32_mkdir (const char *dir, unsigned int mode)
{
  return mkdir (dir);
}

#endif
