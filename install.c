#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include "bin.h"
#include "buffer.h"
#include "error.h"
#include "fmt.h"
#include "install.h"
#include "open.h"
#include "read.h"
#include "str.h"
#include "syserr.h"
#include "write.h"

/* most functions */
static char tmpfrom[MAX_PATHLEN];
static char tmpto[MAX_PATHLEN];

/* install_copy() */
static char bbuf1[4096];
static char bbuf2[4096];
static buffer bin = buffer_INIT(read, -1, bbuf1, sizeof(bbuf1));
static buffer bout = buffer_INIT(write, -1, bbuf2, sizeof(bbuf2));
extern int rename();

/* install_check() and deinstall() */
unsigned int install_failed = 0;
unsigned int deinstall_failed = 0;

static int base_name(const char *dir, char **out)
{
  static char path[MAX_PATHLEN];
  const char *s;
  const char *t;
  const char *u;
  unsigned int len;
  unsigned int nlen;

  len = str_len(dir); 

  if (!len) {
    path[0] = '.';
    path[1] = 0;
    *out = path;
    return 1;
  }

  if (len >= MAX_PATHLEN) return 0;

  s = dir;
  t = s;
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
  bin_copy(u, path, nlen);
  path[nlen] = 0;

  *out = path;
  return 1;
}

static int install_libname(const char *fn, char *buf)
{
  char *s;
  char rbuf[MAX_PATHLEN];
  int n;
  int r;
  int fd;
  int ret;
  int clean;

  ret = 1;
  n = str_rchr(fn, '.');
  if (n == -1) return 0;
  fd = open_ro(fn);
  if (fd == -1) return 0;
  r = read(fd, rbuf, MAX_PATHLEN);
  if (r == 0) { ret = 0; goto END; }
  if (r == -1) {
    syserr_warn3sys("error: open: ", fn, " - "); ret = 0; goto END;
  }
  s = rbuf;
  clean = 0;
  while (r) {
    switch (*s) {
      case ' ':
      case '\t':
      case '\n':
        s[0] = 0;
        clean = 1;
        break;
      default:
        break;
    }
    if (clean) break;
    --r; ++s;
  }
  bin_copy(rbuf, buf, s - rbuf);
  buf[s - rbuf] = 0;

  END:
  if (close(fd) == -1) syserr_warn1sys("error: close: ");
  return ret;
}

/* mangle names and use temporary buffers if necessary */
static int name_mangle(const char **from, const char **to, const char *dir)
{
  unsigned int dirlen;
  unsigned int len;
  const char *pfrom;
  const char *pto;
  char *tbase;

  if (!dir) { syserr_warn1x("error: directory not defined"); return 0; }
  dirlen = str_len(dir);
  if (dirlen >= MAX_PATHLEN) {
    syserr_warn3x("error: ", dir, " path too long"); return 0;
  }

  pfrom = *from;
  pto = *to;

  if (pfrom) {
    if (str_ends(pfrom, ".lib")) {
      if (!install_libname(pfrom, tmpfrom)) return 0;
      pfrom = tmpfrom;
    }
    if (pto) {
      if (str_ends(pto, ".lib")) {
        if (!install_libname(pto, tmpto)) return 0;
        pto = tmpto;
      }
    } else pto = pfrom;
    if (!base_name(pto, &tbase)) {
      syserr_warn3x("error: ", pto, " filename too long"); return 0;
    }
    len = str_len(tbase);
    if (len + dirlen + 1 >= MAX_PATHLEN) {
      syserr_warn1x("error: path too long"); return 0;
    }
    bin_copy(dir, tmpto, dirlen);
    tmpto[dirlen] = '/';
    bin_copy(tbase, tmpto + dirlen + 1, len);
    tmpto[dirlen + len + 1] = 0;
    pto = tmpto;    
  }

  *from = pfrom;
  *to = pto;
  return 1;
}

static int install_rmkdir(const char *path, unsigned int mode)
{
  char pbuf[MAX_PATHLEN];
  const char *ptr;
  unsigned int len;
  unsigned int buflen;
  unsigned int bufpos;
  int pos;
  int end;

  end = 0;
  ptr = path;
  len = str_len(path);
  buflen = MAX_PATHLEN;
  bufpos = 0;
  if (len >= MAX_PATHLEN) return -1;

  for (;;) {
    if (!len) break;
    pos = str_chr(ptr, '/');
    if (pos == -1) {
      pos = len;
      end = 1;
    }
    if (buflen <= (unsigned int) pos + 1) break;
    bin_copy(ptr, pbuf + bufpos, pos);
    bufpos += pos;
    buflen -= pos;
    pbuf[bufpos] = '/';
    ++bufpos;
    --buflen;
    pbuf[bufpos] = 0;
    if (mkdir(pbuf, mode) == -1) {
      if (!end) {
        if (errno != error_exist && errno != error_isdir) return -1;
      } else return -1;
    }
    ptr += pos;
    len -= pos;
    if (len) {
      ++ptr;
      --len;
      if (!len) break;
    }
  }
  return 0;
}

int install_copy(const char *from, const char *to, unsigned int uid,
                 unsigned int gid, unsigned int perm)
{
  char tmpbuf[MAX_PATHLEN];
  char *s;
  unsigned int to_len;
  int r;
  int w;

  to_len = str_len(to);
  if (to_len >= 1019) {
    syserr_warn3x("error: ", to, ".tmp filename too long"); return 0;
  }
  bin_copy(to, tmpbuf, to_len);
  bin_copy(".tmp", tmpbuf + to_len, 4);
  tmpbuf[to_len + 4] = 0;

  bin.fd = open_ro(from);
  if (bin.fd == -1) { syserr_warn3sys("error: open: ", from, " "); goto bad; }
  bout.fd = open_trunc(tmpbuf);
  if (bout.fd == -1) { syserr_warn3sys("error: open: ", tmpbuf, " "); goto bad; }

  for (;;) {
    r = buffer_feed(&bin);
    if (r == 0) break;
    if (r == -1) { syserr_warn1sys("error: read: "); goto bad; }
    s = buffer_peek(&bin);
    w = buffer_put(&bout, s, r);
    if (w == -1) { syserr_warn1sys("error: write: "); goto bad; }
    buffer_seek(&bin, r);
  }

  if (buffer_flush(&bout) == -1) { syserr_warn1sys("error: write: "); goto bad; }
  if (fsync(bout.fd) == -1) { syserr_warn1sys("error: fsync: "); goto bad; }
  if (fchmod(bout.fd, perm)) { syserr_warn1sys("error: fchmod: "); goto bad; }
  if (fchown(bout.fd, uid, gid)) { syserr_warn1sys("error: fchown: "); goto bad; }
  if (rename(tmpbuf, to)) { syserr_warn1sys("error: rename: "); goto bad; }
  if (close(bin.fd) == -1) syserr_warn1sys("error: close: ");
  if (close(bout.fd) == -1) syserr_warn1sys("error: close: ");
  bin.fd = -1;
  bout.fd = -1;

  return 1;

  bad:
  if (bin.fd != -1)
    if (close(bin.fd) == -1) syserr_warn1sys("error: close: ");
  bin.fd = -1;
  if (bout.fd != -1) {
    if (unlink(tmpbuf) == -1)
      if (errno != error_noent)
        syserr_warn3sys("error: unlink: ", tmpbuf, " - ");
    if (close(bout.fd) == -1) syserr_warn1sys("error: close: ");
  }
  bout.fd = -1;
  return 0;
}

int install(const struct install_item *inst, unsigned int flags)
{
  char cnum[FMT_ULONG];
  struct group *grp;
  struct passwd *pwd;
  const char *from;
  const char *to;
  const char *dir;
  const char *owner;
  const char *group;
  unsigned int perm;
  unsigned int uid;
  unsigned int gid;

  from = inst->from;
  to = inst->to;
  dir = inst->dir;
  perm = inst->perm;
  owner = inst->owner;
  group = inst->group;

  if (!owner) { syserr_warn1x("error: owner not defined"); return 0; }
  if (!group) { syserr_warn1x("error: group not defined"); return 0; }

  if (!name_mangle(&from, &to, dir)) return 0;
  if (from) {
    buffer_puts(buffer1, "install ");
    buffer_puts(buffer1, from);
    buffer_puts(buffer1, " ");
    buffer_puts(buffer1, to);
  } else {
    buffer_puts(buffer1, "mkdir ");
    buffer_puts(buffer1, dir);
  }

  buffer_puts(buffer1, " ");
  cnum[fmt_uinto(cnum, perm)] = 0;
  buffer_puts(buffer1, cnum);
  buffer_puts(buffer1, " ");
  buffer_puts(buffer1, owner);
  buffer_puts(buffer1, ":");
  buffer_puts(buffer1, group);
  buffer_puts(buffer1, "\n");
  if (buffer_flush(buffer1) == -1) syserr_warn1sys("error: write: ");

  errno = 0;
  pwd = getpwnam(owner);
  if (!pwd) {
    if (errno) {
      syserr_warn1sys("error: getpwnam: "); return 0;
    } else {
      syserr_warn3x("error: no such user '", owner, "'"); return 0;
    }
  }
  uid = pwd->pw_uid;

  errno = 0;
  grp = getgrnam(group);
  if (!pwd) {
    if (errno) {
      syserr_warn1sys("error: getgrnam: "); return 0;
    } else {
      syserr_warn3x("error: no such group '", group, "'"); return 0;
    }
  }
  gid = grp->gr_gid;

  if (flags & INSTALL_DRYRUN) return 1;

  if (from)
    return install_copy(from, to, uid, gid, perm);
  else
    if (install_rmkdir(dir, perm) == -1) {
      syserr_warn1sys("error: mkdir: "); return 0;
    }

  return 1;
}

int install_check(const struct install_item *inst)
{
  char cnum[FMT_ULONG];
  char cnum2[FMT_ULONG];
  struct group *grp;
  struct passwd *pwd;
  struct stat sb;
  const char *from;
  const char *to;
  const char *dir;
  const char *owner;
  const char *group;
  const char *target;
  unsigned int perm;
  unsigned int uid;
  unsigned int gid;
  int fd;

  from = inst->from;
  to = inst->to;
  dir = inst->dir;
  perm = inst->perm;
  owner = inst->owner;
  group = inst->group;

  if (!dir) { syserr_warn1x("error: directory not defined"); return 0; }
  if (!owner) { syserr_warn1x("error: owner not defined"); return 0; }
  if (!group) { syserr_warn1x("error: group not defined"); return 0; }

  if (!name_mangle(&from, &to, dir)) return 0;
  if (to)
    target = to;
  else
    target = dir;

  buffer_puts(buffer1, "check ");
  buffer_puts(buffer1, target);
  buffer_puts(buffer1, "\n");
  if (buffer_flush(buffer1) == -1) syserr_warn1sys("error: write: ");

  fd = open_ro(target);
  if (fd == -1) {
    syserr_warn3sys("error: open: ", target, " ");
    ++install_failed;
    return 0;
  }

  errno = 0;
  pwd = getpwnam(owner);
  if (!pwd) {
    if (errno) {
      syserr_warn1sys("error: getpwnam: "); ++install_failed; goto ERR;
    } else {
      syserr_warn3x("error: no such user '", owner, "'");
      ++install_failed;
      goto ERR;
    }
  }
  uid = pwd->pw_uid;

  errno = 0;
  grp = getgrnam(group);
  if (!pwd) {
    if (errno) {
      syserr_warn1sys("error: getgrnam: "); ++install_failed; goto ERR;
    } else {
      syserr_warn3x("error: no such group '", group, "'");
      ++install_failed;
      goto ERR;
    }
  }
  gid = grp->gr_gid;

  if (fstat(fd, &sb)) {
    syserr_warn3sys("error: fstat: ", target, " "); goto ERR;
  }

  if (uid != sb.st_uid) {
    cnum[fmt_ulong(cnum, sb.st_uid)] = 0;
    cnum2[fmt_ulong(cnum2, uid)] = 0;
    syserr_warn4x("error: file uid ", cnum, " does not match expected uid ", cnum2);
    ++install_failed;
    goto ERR;
  }
  if (gid != sb.st_gid) {
    cnum[fmt_ulong(cnum, sb.st_gid)] = 0;
    cnum2[fmt_ulong(cnum2, gid)] = 0;
    syserr_warn4x("error: file gid ", cnum, " does not match expected gid ", cnum2);
    ++install_failed;
    goto ERR;
  }

  /* if from was specified, target must be regular file */
  if (from) {
    if ((sb.st_mode & S_IFMT) != S_IFREG) {
      syserr_warn3x("error: ", target, " is not a regular file");
      ++install_failed;
      goto ERR;
    }
  } else {
    if ((sb.st_mode & S_IFMT) != S_IFDIR) {
      syserr_warn3x("error: ", target, " is not a directory");
      ++install_failed;
      goto ERR;
    }
  }
 
  if ((sb.st_mode & 07777) != perm) {
    cnum[fmt_ulongo(cnum, sb.st_mode & 07777)] = 0;
    cnum2[fmt_ulongo(cnum2, perm)] = 0;
    syserr_warn4x("error: file mode ", cnum, " does not match expected mode ", cnum2);
    ++install_failed;
    goto ERR;
  }

  ERR:
  if (close(fd) == -1)
    syserr_warn3sys("error: close: ", target, " ");

  return 1;
}

int deinstall(const struct install_item *inst, unsigned int flags)
{
  const char *from;
  const char *to;
  const char *dir;
  const char *target;

  from = inst->from;
  to = inst->to;
  dir = inst->dir;

  if (!dir) { syserr_warn1x("error: directory not defined"); return 0; }
  if (!name_mangle(&from, &to, dir)) return 0;
  if (to) {
    target = to;
    buffer_puts(buffer1, "unlink ");
    buffer_puts(buffer1, target);
    buffer_puts(buffer1, "\n");
    if (buffer_flush(buffer1) == -1) syserr_warn1x("error: write: ");
    if (flags & INSTALL_DRYRUN) return 1;
    if (unlink(target) == -1) {
      syserr_warn3sys("error: unlink: ", target, " ");
      ++deinstall_failed;
      return 0;
    }
  } else {
    target = dir;
    buffer_puts(buffer1, "rmdir ");
    buffer_puts(buffer1, target);
    buffer_puts(buffer1, "\n");
    if (buffer_flush(buffer1) == -1) syserr_warn1x("error: write: ");
    if (flags & INSTALL_DRYRUN) return 1;
    if (rmdir(target) == -1) {
      syserr_warn3sys("error: rmdir: ", target, " ");
      ++deinstall_failed;
      return 0;
    }
  }
  return 1;
}
