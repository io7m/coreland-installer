#include <errno.h>
#include <stdio.h>
#include <string.h>

#include <sys/types.h>
#include <sys/stat.h>

#include "install.h"

#if INSTALL_OS_TYPE == INSTALL_OS_POSIX
#include <unistd.h>
#endif

#if INSTALL_OS_TYPE == INSTALL_OS_WIN32
#include <io.h>
#endif

#define COPYBUF_SIZE 8192

static char copy_buf[COPYBUF_SIZE];
static char src_name[INSTALL_MAX_PATHLEN];
static char dst_name[INSTALL_MAX_PATHLEN];
static char src_tmp[INSTALL_MAX_PATHLEN];
static char dst_tmp[INSTALL_MAX_PATHLEN];
static char tmp_buf[INSTALL_MAX_PATHLEN];
static char cmdline_buf [INSTALL_MAX_PATHLEN];

/* installation tools */
#define EXT_INST_COPY ext_tools[0]
#define EXT_INST_CHECK ext_tools[1]
#define EXT_INST_DIR ext_tools[2]
#define EXT_INST_LINK ext_tools[3]
#define EXT_INST_SOSUFFIX ext_tools[4]
static char *ext_tools[] = {
  "./inst-copy",
  "./inst-check",
  "./inst-dir",
  "./inst-link",
  "./mk-sosuffix",
};

unsigned long install_failed;

/* error functions */

int
fails_sys (const char *s)
{
  printf ("failed: %s: %s\n", s, install_error (errno));
  return 0;
}

int
fails (const char *s)
{
  printf ("failed: %s\n", s);
  return 0;
}

void
fail (void)
{
  printf ("failed: %s\n", install_error (errno));
}

void
fail_noread (void)
{
  printf ("failed: no bytes read\n");
}

/* credential functions */

int
install_file_set_ownership (const char *file, user_id_t uid, group_id_t gid)
{
#if INSTALL_OS_TYPE == INSTALL_OS_POSIX
  return iposix_file_set_ownership (file, uid, gid);
#endif
#if INSTALL_OS_TYPE == INSTALL_OS_WIN32
  return iwin32_file_set_ownership (file, uid, gid);
#endif
}

int
install_file_get_ownership (const char *file, user_id_t *uid, group_id_t *gid)
{
#if INSTALL_OS_TYPE == INSTALL_OS_POSIX
  return iposix_file_get_ownership (file, uid, gid);
#endif
#if INSTALL_OS_TYPE == INSTALL_OS_WIN32
  return iwin32_file_get_ownership (file, uid, gid);
#endif
}

int
install_file_get_mode (const char *file, unsigned int *mode)
{
#if INSTALL_OS_TYPE == INSTALL_OS_POSIX
  return iposix_file_get_mode (file, mode);
#endif
#if INSTALL_OS_TYPE == INSTALL_OS_WIN32
  return iwin32_file_get_mode (file, mode);
#endif
}

int
install_gid_current (group_id_t *gid)
{
#if INSTALL_OS_TYPE == INSTALL_OS_POSIX
  return iposix_gid_current (gid);
#endif
#if INSTALL_OS_TYPE == INSTALL_OS_WIN32
  return iwin32_gid_current (gid);
#endif
}

int
install_uid_current (user_id_t *uid)
{
#if INSTALL_OS_TYPE == INSTALL_OS_POSIX
  return iposix_uid_current (uid);
#endif
#if INSTALL_OS_TYPE == INSTALL_OS_WIN32
  return iwin32_uid_current (uid);
#endif
}

int
install_gid_lookup (const char *name, group_id_t *gid)
{
#if INSTALL_OS_TYPE == INSTALL_OS_POSIX
  return iposix_gid_lookup (name, gid);
#endif
#if INSTALL_OS_TYPE == INSTALL_OS_WIN32
  return iwin32_gid_lookup (name, gid);
#endif
}

int
install_uid_lookup (const char *name, user_id_t *uid)
{
#if INSTALL_OS_TYPE == INSTALL_OS_POSIX
  return iposix_uid_lookup (name, uid);
#endif
#if INSTALL_OS_TYPE == INSTALL_OS_WIN32
  return iwin32_uid_lookup (name, uid);
#endif
}

unsigned int
install_fmt_gid (char *buffer, group_id_t gid)
{
#if INSTALL_OS_TYPE == INSTALL_OS_POSIX
  return iposix_fmt_gid (buffer, gid);
#endif
#if INSTALL_OS_TYPE == INSTALL_OS_WIN32
  return iwin32_fmt_gid (buffer, gid);
#endif
}

unsigned int
install_fmt_uid (char *buffer, user_id_t uid)
{
#if INSTALL_OS_TYPE == INSTALL_OS_POSIX
  return iposix_fmt_uid (buffer, uid);
#endif
#if INSTALL_OS_TYPE == INSTALL_OS_WIN32
  return iwin32_fmt_uid (buffer, uid);
#endif
}

unsigned int
install_scan_gid (const char *buffer, group_id_t *gid)
{
#if INSTALL_OS_TYPE == INSTALL_OS_POSIX
  return iposix_scan_gid (buffer, gid);
#endif
#if INSTALL_OS_TYPE == INSTALL_OS_WIN32
  return iwin32_scan_gid (buffer, gid);
#endif
}

unsigned int
install_scan_uid (const char *buffer, user_id_t *uid)
{
#if INSTALL_OS_TYPE == INSTALL_OS_POSIX
  return iposix_scan_uid (buffer, uid);
#endif
#if INSTALL_OS_TYPE == INSTALL_OS_WIN32
  return iwin32_scan_uid (buffer, uid);
#endif
}

int
install_compare_uid (user_id_t a, user_id_t b)
{
#if INSTALL_OS_TYPE == INSTALL_OS_POSIX
  return iposix_compare_uid (a, b);
#endif
#if INSTALL_OS_TYPE == INSTALL_OS_WIN32
  return iwin32_compare_uid (a, b);
#endif
}

int
install_compare_gid (group_id_t a, group_id_t b)
{
#if INSTALL_OS_TYPE == INSTALL_OS_POSIX
  return iposix_compare_gid (a, b);
#endif
#if INSTALL_OS_TYPE == INSTALL_OS_WIN32
  return iwin32_compare_gid (a, b);
#endif
}

/* portability macro */
#ifndef S_ISSOCK
#  if defined(S_IFMT) && defined(S_IFSOCK)
#    define S_ISSOCK(mode) (((mode) & S_IFMT) == S_IFSOCK)
#  else
#    define S_ISSOCK(mode)
#  endif
#endif

int s_ifreg (unsigned int m)  { return S_ISREG(m); }
int s_ifchr (unsigned int m)  { return S_ISCHR(m); }
int s_ifdir (unsigned int m)  { return S_ISDIR(m); }
int s_iflnk (unsigned int m)  { return S_ISLNK(m); }
int s_ifsock (unsigned int m) { return S_ISSOCK(m); }
int s_ififo (unsigned int m)  { return S_ISFIFO(m); }

static const struct {
  int (*check)(unsigned int);
  const char *name;
  const enum install_file_type_t type;
} file_type_lookups[] = {
  { &s_ifreg,  "file",              INSTALL_FILE_TYPE_FILE },
  { &s_ifchr,  "character_special", INSTALL_FILE_TYPE_CHARACTER_SPECIAL },
  { &s_ifdir,  "directory",         INSTALL_FILE_TYPE_DIRECTORY },
  { &s_iflnk,  "symlink",           INSTALL_FILE_TYPE_SYMLINK },
  { &s_ifsock, "socket",            INSTALL_FILE_TYPE_SOCKET },
  { &s_ififo,  "fifo",              INSTALL_FILE_TYPE_FIFO },
};
static const unsigned int file_type_lookups_size =
  sizeof (file_type_lookups) / sizeof (file_type_lookups[0]);

int
install_file_type (const char *file, enum install_file_type_t *type, int nofollow)
{
  struct stat sb;
  unsigned int index;

  if (nofollow) {
    if (lstat (file, &sb) == -1) return 0;
  } else {
    if (stat (file, &sb) == -1) return 0;
  }

  for (index = 0; index < file_type_lookups_size; ++index) {
    if (file_type_lookups [index].check (sb.st_mode)) {
      *type = file_type_lookups [index].type;
      return 1;
    }
  }
  return 0;
}

int
install_file_type_lookup (const char *type_name, enum install_file_type_t *type)
{
  unsigned int index;
  for (index = 0; index < file_type_lookups_size; ++index) {
    if (strcmp (file_type_lookups [index].name, type_name) == 0) {
      *type = file_type_lookups [index].type;
      return 1;
    }
  }
  return 0;
}

int
install_file_type_name_lookup (enum install_file_type_t type, const char **name)
{
  unsigned int index;
  for (index = 0; index < file_type_lookups_size; ++index) {
    if (file_type_lookups [index].type == type) {
      *name = file_type_lookups [index].name;
      return 1;
    }
  }
  return 0;
}

int
install_file_set_mode (const char *file, unsigned int mode)
{
  if (chmod (file, mode) == -1) return 0;
  return 1;
}

int
install_file_copy (const char *src, const char *dst,
  user_id_t uid, group_id_t gid, unsigned int mode)
{
  FILE *fd_src;
  FILE *fd_dst;
  size_t r;
  size_t w;

  if (snprintf (dst_tmp, sizeof (dst_tmp), "%s.tmp", dst) < 0) return 0;

  fd_src = fopen (src, "rb");
  if (fd_src == NULL) return 0;
  fd_dst = fopen (dst_tmp, "wb");
  if (fd_dst == NULL) goto ERR;

  for (;;) {
    r = fread (copy_buf, 1, COPYBUF_SIZE, fd_src);
    if (r == 0) {
      if (feof (fd_src)) break;
      if (ferror (fd_src)) goto ERR;
    }
    while (r) {
      w = fwrite (copy_buf, 1, r, fd_dst);
      if (w == 0) {
        if (feof (fd_src)) break;
        if (ferror (fd_src)) goto ERR;
      }
      r -= w;
    }
  }

  if (fflush (fd_dst) != 0) goto ERR;
  if (!install_file_set_mode (dst_tmp, mode)) goto ERR;
  if (!install_file_set_ownership (dst_tmp, uid, gid)) goto ERR;
  if (rename (dst_tmp, dst) == -1) goto ERR;
  if (fclose (fd_dst) == -1) goto ERR;
  if (fclose (fd_src) == -1) goto ERR;

  return 1;
  ERR:
  unlink (dst_tmp);
  return 0;
}

int
install_file_size (const char *file, unsigned long *size)
{
  struct stat sb;

  if (stat (file, &sb) == -1) return 0;

  *size = sb.st_size;
  return 1;
}

int
install_file_link (const char *src, const char *dst)
{
#if INSTALL_OS_TYPE == INSTALL_OS_POSIX
  return iposix_file_link (src, dst);
#endif
#if INSTALL_OS_TYPE == INSTALL_OS_WIN32
  return iwin32_file_link (src, dst);
#endif
}

/* portability functions */

int
base_name (const char *dir, char **out)
{
  static char path[INSTALL_MAX_PATHLEN];
  const char *s;
  const char *t;
  const char *u;
  unsigned int len;
  unsigned int nlen;

  len = strlen (dir); 

  if (!len) {
    path[0] = '.';
    path[1] = 0;
    *out = path;
    return 1;
  }

  if (len >= INSTALL_MAX_PATHLEN) return 0;

  s = dir;
  t = s + (len - 1);
  while ((t > s) && (t[0] == '/')) --t;

  if ((t == s) && (t[0] == '/')) {
    path[0] = '/';
    path[1] = 0;
    *out = path;
    return 1;
  }
  u = t;
  while ((u > s) && (*(u - 1) != '/')) --u;

  nlen = (t - u) + 1;
  memcpy (path, u, nlen);
  path[nlen] = 0;

  *out = path;
  return 1;
}

int
str_same (const char *a, const char *b)
{
  return strcmp (a, b) == 0;
}

int
str_ends (const char *s, const char *end)
{
  register unsigned long slen = strlen (s);
  register unsigned long elen = strlen (end);

  if (elen > slen) elen = slen;
  s += (slen - elen);
  return str_same (s, end);
}

/* utilities */

int
libname (char *name, char *buf)
{
  FILE *fp;
  char *s;
  char rbuf[INSTALL_MAX_PATHLEN];
  size_t r;
  int ret = 1;
  int clean;

  fp = fopen (name, "rb");
  if (fp == NULL) return fails_sys (name);

  r = fread (rbuf, 1, INSTALL_MAX_PATHLEN, fp);
  if (r < INSTALL_MAX_PATHLEN) {
    if (ferror (fp)) {
      fails_sys (name);
      ret = 0;
      goto END;
    }
  }

  /* clean whitespace from buffer */
  s = rbuf;
  clean = 0;
  while (r) {
    switch (*s) {
      case ' ':
      case '\t':
      case '\n':
      case '\r':
        s[0] = 0;
        clean = 1;
        break;
      default:
        break;
    }
    if (clean) break;
    --r;
    ++s;
  }
  memcpy (buf, rbuf, s - rbuf);
  buf[s - rbuf] = 0;

  END:
  if (fclose (fp) != 0) fails_sys (name);
  return ret;
}

static int
run_command (const char *cmd)
{
  FILE *fp;
  int exit_code;
  char buf[256];
  size_t size;

  fp = popen (cmdline_buf, "r");
  if (!fp) { fails_sys ("popen"); return -1; }

  for (;;) {
    size = fread (buf, 1, sizeof (buf), fp);
    if (size == 0) {
      if (ferror (fp)) { fails_sys ("read"); }
      break;
    }
    fwrite (buf, size, 1, stdout);
  }

  exit_code = pclose (fp);
  if (exit_code == -1) { fails_sys ("pclose"); return -1; }
  return exit_code;
}

/* install operator callbacks */

int
inst_copy (struct install_item *ins, unsigned int flags)
{
  const char *owner = (ins->owner) ? ins->owner : INSTALL_NULL_USER_NAME;
  const char *group = (ins->group) ? ins->group : INSTALL_NULL_GROUP_NAME;

  /* build command line */
  snprintf (cmdline_buf, sizeof (cmdline_buf), "%s %s %s %s %s %o %s",
    EXT_INST_COPY, ins->src, ins->dst, owner, group, ins->perm,
    (flags & INSTALL_DRYRUN) ? "dryrun" : "");

  return run_command (cmdline_buf) == 0;
}

int
inst_link (struct install_item *ins, unsigned int flags)
{
  /* build command line */
  snprintf (cmdline_buf, sizeof (cmdline_buf), "%s %s %s %s %s",
    EXT_INST_LINK, ins->dir, ins->src, ins->dst,
    (flags & INSTALL_DRYRUN) ? "dryrun" : "");

  return run_command (cmdline_buf) == 0;
}

int
inst_mkdir (struct install_item *ins, unsigned int flags)
{
  const char *owner = (ins->owner) ? ins->owner : INSTALL_NULL_USER_NAME;
  const char *group = (ins->group) ? ins->group : INSTALL_NULL_GROUP_NAME;

  /* build command line */
  snprintf (cmdline_buf, sizeof (cmdline_buf), "%s %s %s %s %o %s",
    EXT_INST_DIR, ins->dir, owner, group, ins->perm,
    (flags & INSTALL_DRYRUN) ? "dryrun" : "");

  return run_command (cmdline_buf) == 0;
}

int
inst_liblink (struct install_item *ins, unsigned int flags)
{
  return inst_link (ins, flags);
}

/*
 * name translation callbacks
 */

int
ntran_copy (struct install_item *ins)
{
  if (!ins->src) return fails ("src file undefined");
  if (!ins->dir) return fails ("directory unefined");
  if (!ins->dst) ins->dst = ins->src;

  if (str_ends (ins->src, ".vlb")) {
    if (!libname (ins->src, src_name)) return 0;
    ins->src = src_name;
  }
  if (str_ends (ins->dst, ".vlb")) {
    if (!libname (ins->dst, dst_name)) return 0;
    ins->dst = dst_name;
  }

  if (!base_name (ins->dst, &ins->dst)) return fails ("invalid path");
  if (snprintf (dst_tmp, INSTALL_MAX_PATHLEN, "%s/%s", ins->dir, ins->dst) < 0)
    return fails_sys ("snprintf");

  ins->dst = dst_tmp;
  return 1;
}

int
ntran_link (struct install_item *ins)
{
  if (!ins->src) return fails ("src file undefined");
  if (!ins->dir) return fails ("directory unefined");
  if (!ins->dst) return fails ("dst name undefined");
  return 1;
}

int
ntran_liblink (struct install_item *ins)
{
  FILE *fp;
  size_t size;

  if (!ins->src) return fails("src file undefined");
  if (!ins->dir) return fails("directory unefined");
  if (!ins->dst) return fails("dst name undefined");

  if (str_ends (ins->src, ".vlb")) {
    if (!libname (ins->src, src_tmp)) return 0;
    ins->src = src_tmp;
    if (!base_name (ins->src, &ins->src)) return fails("invalid path");
    memcpy (src_name, ins->src, INSTALL_MAX_PATHLEN);
    ins->src = src_name;
  }

  /* build command line */
  snprintf (cmdline_buf, sizeof (cmdline_buf), "%s", EXT_INST_SOSUFFIX);

  fp = popen (cmdline_buf, "r");
  if (!fp) { fails_sys ("popen"); return 0; }

  size = fread (tmp_buf, 1, sizeof (tmp_buf), fp);
  if (size == 0) {
    if (feof (fp)) { fail_noread (); return 0; }
    if (ferror (fp)) { fails_sys ("ferror"); return 0; }
  }
  tmp_buf[size - 1] = 0;

  if (pclose (fp) == -1) { fails_sys ("pclose"); return 0; }
 
  /* build name of library */
  if (!base_name (ins->dst, &ins->dst)) return fails("invalid path");
  if (snprintf (dst_tmp, INSTALL_MAX_PATHLEN, "%s.%s", ins->dst, tmp_buf) < 0)
    return fails_sys ("snprintf");
  ins->dst = dst_tmp;

  return 1;
}

int
ntran_mkdir (struct install_item *ins)
{
  if (!ins->dst) ins->dst = ins->src;
  return 1;
}

int
ntran_chk_link (struct install_item *ins)
{
  if (!ntran_link (ins)) return 0;
  if (snprintf (dst_name, INSTALL_MAX_PATHLEN, "%s/%s", ins->dir, ins->dst) < 0)
    return fails_sys ("sprintf");

  ins->dst = dst_name;
  return 1;
}

int
ntran_chk_liblink (struct install_item *ins)
{
  if (!ntran_liblink (ins)) return 0;
  if (snprintf (dst_name, INSTALL_MAX_PATHLEN, "%s/%s", ins->dir, ins->dst) < 0)
    return fails_sys ("sprintf");

  ins->dst = dst_name;
  return 1;
}

/*
 * instchk operator callbacks
 */

int
instchk_copy (struct install_item *ins, unsigned int flags)
{
  /* build command line */
  snprintf (cmdline_buf, sizeof (cmdline_buf), "%s %s %s %s %s %o file",
    EXT_INST_CHECK, ins->src, ins->dst, INSTALL_NULL_USER_NAME,
    INSTALL_NULL_GROUP_NAME, ins->perm);

  if (run_command (cmdline_buf) != 0) {
    ++install_failed;
    return 0;
  }
  return 1;
}

int
instchk_link (struct install_item *ins, unsigned int flags)
{
  /* build command line */
  snprintf (cmdline_buf, sizeof (cmdline_buf), "%s %s %s %s %s %o symlink",
    EXT_INST_CHECK, ins->src, ins->dst, INSTALL_NULL_USER_NAME,
    INSTALL_NULL_GROUP_NAME, ins->perm);

  if (run_command (cmdline_buf) != 0) {
    ++install_failed;
    return 0;
  }
  return 1;
}

int
instchk_mkdir (struct install_item *ins, unsigned int flags)
{
  /* build command line */
  snprintf (cmdline_buf, sizeof (cmdline_buf), "%s %s %s %s %s %o directory",
    EXT_INST_CHECK, ins->dir, ins->dir, INSTALL_NULL_USER_NAME,
    INSTALL_NULL_GROUP_NAME, ins->perm);

  if (run_command (cmdline_buf) != 0) {
    ++install_failed;
    return 0;
  }
  return 1;
}

int
instchk_liblink (struct install_item *ins, unsigned int flags)
{
  return instchk_link (ins, flags);
}

/*
 * deinstall operator callbacks
 */

int
deinst_copy (struct install_item *ins, unsigned int flags)
{
  printf("unlink %s\n", ins->dst);
  if (flags & INSTALL_DRYRUN) return 1;
  if (unlink(ins->dst) == -1) return fails_sys ("unlink");
  return 1;
}

int
deinst_link (struct install_item *ins, unsigned int flags)
{
  printf ("unlink %s/%s\n", ins->dir, ins->dst);
  if (snprintf (tmp_buf, INSTALL_MAX_PATHLEN, "%s/%s", ins->dir, ins->dst) < 0)
    return fails_sys ("snprintf");
  ins->dst = tmp_buf;

  if (flags & INSTALL_DRYRUN) return 1;
  if (unlink(ins->dst) == -1) return fails_sys ("unlink");
  return 1;
}

int
deinst_mkdir (struct install_item *ins, unsigned int flags)
{
  printf ("rmdir %s\n", ins->dir);
  if (flags & INSTALL_DRYRUN) return 1;
  if (rmdir (ins->dir) == -1) return fails_sys ("rmdir");
  return 1;
}

int
deinst_liblink (struct install_item *ins, unsigned int flags)
{
  return deinst_link (ins, flags);
}

/*
 * operator callback tables
 */

struct instop {
  int (*oper) (struct install_item *, unsigned int);
  int (*trans) (struct install_item *);
};
struct instop install_opers[] = {
  { inst_copy, ntran_copy },
  { inst_link, ntran_link },
  { inst_mkdir, ntran_mkdir },
  { inst_liblink, ntran_liblink },
};
struct instop instchk_opers[] = {
  { instchk_copy, ntran_copy },
  { instchk_link, ntran_chk_link },
  { instchk_mkdir, ntran_mkdir },
  { instchk_liblink, ntran_chk_liblink },
};
struct instop deinst_opers[] = {
  { deinst_copy, ntran_copy },
  { deinst_link, ntran_link },
  { deinst_mkdir, ntran_mkdir },
  { deinst_liblink, ntran_liblink },
};

/*
 * interface
 */

int
install_init (void)
{
#if INSTALL_OS_TYPE == INSTALL_OS_POSIX
  return iposix_install_init ();
#endif
#if INSTALL_OS_TYPE == INSTALL_OS_WIN32
  return iwin32_install_init ();
#endif
}

int
install (struct install_item *ins, unsigned int flags)
{
  int r = 1;

  r = install_opers[ins->op].trans (ins);
  if (!r) goto CLEANUP;
  r = install_opers[ins->op].oper (ins, flags);

  CLEANUP:
  fflush (0);
  return r;
}

int
install_check (struct install_item *ins)
{
  int r = 1;

  r = instchk_opers[ins->op].trans (ins);
  if (!r) goto CLEANUP;
  r = instchk_opers[ins->op].oper (ins, 0);

  CLEANUP:
  fflush (0);
  return r;
}

int
deinstall(struct install_item *ins, unsigned int flags)
{
  int r = 1;

  r = deinst_opers[ins->op].trans (ins);
  if (!r) goto CLEANUP;
  r = deinst_opers[ins->op].oper (ins, 0);

  CLEANUP:
  fflush (0);
  return r;
}
