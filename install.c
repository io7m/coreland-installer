#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h> /* rename() */
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

/* these functions are included inline to reduce dependencies
 * it's not reasonable to expect a project to include all these
 * files just for the installer.
 */

#define sstr_INIT(s) { (s), (0), (sizeof s) }
struct sstr {
  char *s;
  unsigned int len;
  unsigned int a;
};
unsigned int sstr_catb(struct sstr *ss, const char *s, unsigned int len)
{
  register unsigned int n;
  register char* ssp;
  n = len; ssp = ss->s;
  
  if (ss->len == ss->a) return 0;
  if ((ss->len + n) > ss->a) n = ss->a - ss->len; /* refuse overflow */
  ssp += ss->len;
  for (;;) {
    if (!n) break; *ssp++ = *s++; --n;
    if (!n) break; *ssp++ = *s++; --n;
    if (!n) break; *ssp++ = *s++; --n;
    if (!n) break; *ssp++ = *s++; --n;
  }
  return ss->len = ssp - ss->s;
}
unsigned int sstr_cats(struct sstr *ss, const char *s)
{
  register const char* t;
  for (t = s;;) {
    if (!*t) return sstr_catb(ss, s, t - s); ++t;
    if (!*t) return sstr_catb(ss, s, t - s); ++t;
    if (!*t) return sstr_catb(ss, s, t - s); ++t;
    if (!*t) return sstr_catb(ss, s, t - s); ++t;
  }
}
unsigned int sstr_0(struct sstr *ss)
{
  if (ss->len == ss->a) ss->len--;
  ss->s[ss->len] = 0; return ss->len;
}
unsigned int sstr_chop(struct sstr *ss, unsigned int len)
{
  char *str;
  if (len >= ss->a) return ss->a;
  str = ss->s;
  str[len] = 0;
  ss->len = len;
  return len;
}
void sstr_trunc(struct sstr *ss)
{
  ss->len = 0;
}
unsigned int scan_charset(const char *s, const char *chars)
{
  unsigned int len;
  const char *cmp;
  char ch;

  len = 0;
  for (;;) {
    ch = s[len];
    if (!ch) break;
    for (cmp = chars;;) {
      if (!*cmp) return len; if (*cmp == ch) { ++len; break; } ++cmp;
      if (!*cmp) return len; if (*cmp == ch) { ++len; break; } ++cmp;
      if (!*cmp) return len; if (*cmp == ch) { ++len; break; } ++cmp;
      if (!*cmp) return len; if (*cmp == ch) { ++len; break; } ++cmp;
    }
  }
  return len;
}
unsigned int scan_notcharset(const char *s, const char *chars)
{
  unsigned int len;
  const char *cmp;
  char ch;

  len = 0;
  for (;;) {
    ch = s[len];
    if (!ch) break;
    for (cmp = chars;;) {
      if (!*cmp) break; if (*cmp == ch) return len; ++cmp;
      if (!*cmp) break; if (*cmp == ch) return len; ++cmp;
      if (!*cmp) break; if (*cmp == ch) return len; ++cmp;
      if (!*cmp) break; if (*cmp == ch) return len; ++cmp;
    }
    ++len;
  }
  return len;
}

static char tfr[MAX_PATHLEN];
static char tfl[MAX_PATHLEN];
static char tto[MAX_PATHLEN];
static char tmpbuf[MAX_PATHLEN];
static struct sstr tmpto = sstr_INIT(tto);
static struct sstr tmpfrom = sstr_INIT(tfr);
static struct sstr tmpfn = sstr_INIT(tfl);

static char bbuf_i[BUFFER_INSIZE];
static char bbuf_o[BUFFER_OUTSIZE];
static buffer ibuf = buffer_INIT(read, -1, bbuf_i, sizeof(bbuf_i));
static buffer obuf = buffer_INIT(write, -1, bbuf_o, sizeof(bbuf_o));

unsigned int install_failed;
unsigned int deinstall_failed;

static int conv_uidgid(const char *sid, int *uid,
                       const char *sgd, int *gid)
{
  struct group *grp;
  struct passwd *pwd;

  if (sid) {
    errno = 0;
    pwd = getpwnam(sid);
    if (!pwd) {
      if (errno) {
        syserr_warn1sys("error: getpwnam: "); return 0;
      } else {
        syserr_warn3x("error: no such user '", sid, "'"); return 0;
      }
    }
    *uid = pwd->pw_uid;
  } else *uid = -1;

  if (sgd) {
    errno = 0;
    grp = getgrnam(sgd);
    if (!pwd) {
      if (errno) {
        syserr_warn1sys("error: getgrnam: "); return 0;
      } else {
        syserr_warn3x("error: no such group '", sgd, "'"); return 0;
      }
    }
    *gid = grp->gr_gid;
  } else *gid = -1;

  return 1;
}
static int libname(const char *fn, char *buf)
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
  if (fd == -1) {
    syserr_warn3sys("error: open: ", fn, " - "); return 0;
  }
  r = read(fd, rbuf, MAX_PATHLEN);
  if (r == 0) { ret = 0; goto END; }
  if (r == -1) {
    syserr_warn3sys("error: read: ", fn, " - "); ret = 0; goto END;
  }
  s = rbuf;
  clean = 0;
  while (r) {
    switch (*s) {
      case ' ': case '\t': case '\n':
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
static int rmkdir(const char *path, unsigned int mode)
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
void print_op(const char *op, const char *from, const char *to,
              const char *own, const char *group, unsigned int perm)
{
  char cnum[FMT_ULONG];
  buffer_puts(buffer1, op);
  buffer_puts(buffer1, " ");
  if (from) { buffer_puts(buffer1, from); buffer_puts(buffer1, " "); }
  if (to) { buffer_puts(buffer1, to); buffer_puts(buffer1, " "); }
  if (perm) {
    cnum[fmt_uinto(cnum, perm)] = 0;
    buffer_puts(buffer1, cnum); buffer_puts(buffer1, " ");
  }
  if (own) { buffer_puts(buffer1, own); buffer_puts(buffer1, ":"); }
  if (group) buffer_puts(buffer1, group);
  if (buffer_putsflush(buffer1, "\n") == -1)
    syserr_warn1sys("error: write: ");
}
static int chkf(int fd, const char *f, int uid, int gid,
                unsigned int perm, int type, const char *typestr)
{
  char cnum1[FMT_ULONG];
  char cnum2[FMT_ULONG];
  struct stat sb;

  if (fd == -1) {
    if (type == S_IFLNK) {
      if (lstat(f, &sb) == -1) {
        syserr_warn3sys("error: lstat: ", f, " - ");
        ++install_failed;
        return 0;
      }
    } else {
      if (stat(f, &sb) == -1) {
        syserr_warn3sys("error: stat: ", f, " - ");
        ++install_failed;
        return 0;
      }
    }
  } else {
    if (fstat(fd, &sb) == -1) {
      syserr_warn3sys("error: fstat: ", f, " - "); /* not an install error */
      return 0;
    }
  }
  if ((sb.st_mode & S_IFMT) != type) {
    syserr_warn4x("error: ", f, " - not a ", typestr);
    ++install_failed;
    return 0;
  }
  if (perm) {
    if ((sb.st_mode & 0777) != (int) perm) {
      cnum1[fmt_uinto(cnum1, perm)] = 0;
      cnum2[fmt_uinto(cnum2, sb.st_mode & 0777)] = 0;
      syserr_warn4x("error: wrong mode - wanted ", cnum1, " got ", cnum2);
      ++install_failed;
      return 0;
    }
  }
  if (uid != -1) {
    if (sb.st_uid != (uid_t) uid) {
      cnum1[fmt_uint(cnum1, uid)] = 0;
      cnum2[fmt_uint(cnum2, sb.st_uid)] = 0;
      syserr_warn4x("error: wrong uid - wanted ", cnum1, " got ", cnum2);
      ++install_failed;
      return 0;
    }
  }
  if (gid != -1) {
    if (sb.st_gid != (uid_t) gid) {
      cnum1[fmt_uint(cnum1, gid)] = 0;
      cnum2[fmt_uint(cnum2, sb.st_gid)] = 0;
      syserr_warn4x("error: wrong gid - wanted ", cnum1, " got ", cnum2);
      ++install_failed;
      return 0;
    }
  }
  return 1;
}

static int ntrans_copy(const char **pfrom, const char **pto, const char *dir)
{
  const char *from;
  const char *to;

  from = *pfrom;
  to = *pto;

  if (!from) { syserr_warn1x("error: from file not defined"); return 0; }
  if (!dir) { syserr_warn1x("error: directory not defined"); return 0; }
  if (!to) to = from;

  sstr_trunc(&tmpfrom);
  sstr_trunc(&tmpto);

  if (str_ends(from, ".lib")) {
    if (!libname(from, tmpbuf)) return 0;
    from = tmpbuf;
  }
  sstr_cats(&tmpfrom, from);
  sstr_0(&tmpfrom);

  sstr_cats(&tmpto, dir);
  sstr_cats(&tmpto, "/");
  if (str_ends(to, ".lib")) {
    if (!libname(to, tmpbuf)) return 0;
    to = tmpbuf;
  }
  if (!base_name(to, (char **) &to)) return 0;
  sstr_cats(&tmpto, to);
  sstr_0(&tmpto);

  from = tmpfrom.s;
  to = tmpto.s;

  *pfrom = from;
  *pto = to;
  return 1; 
}
static int instop_copy(struct install_item *ins, int uid, int gid,
                       unsigned int flag)
{
  const char *from;
  const char *to;
  char *s;
  int r;
  int w;
  unsigned int perm;

  from = ins->from;
  to = ins->to;
  perm = ins->perm;

  print_op("install", from, to, ins->owner, ins->group, ins->perm);
  if (flag & INSTALL_DRYRUN) return 1;

  /* copy */
  sstr_trunc(&tmpfn);
  sstr_cats(&tmpfn, to);
  sstr_cats(&tmpfn, ".tmp");
  sstr_0(&tmpfn);

  obuf.fd = open_trunc(tmpfn.s);
  if (obuf.fd == -1) {
    syserr_warn3sys("error: open: ", tmpfn.s, " - "); goto ERROR;
  }
  ibuf.fd = open_ro(from);
  if (ibuf.fd == -1) {
    syserr_warn3sys("error: open: ", from, " - "); goto ERROR;
  } 

  for (;;) {
    r = buffer_feed(&ibuf);
    if (r == 0) break;
    if (r == -1) { syserr_warn1sys("error: read: "); goto ERROR; }
    s = buffer_peek(&ibuf);
    w = buffer_put(&obuf, s, r);
    if (w == -1) { syserr_warn1sys("error: write: "); goto ERROR; }
    buffer_seek(&ibuf, r);
  }
  if (buffer_flush(&obuf) == -1) {
    syserr_warn3sys("error: write: ", tmpfn.s, " - "); goto ERROR;
  }
  if (fsync(obuf.fd) == -1) {
    syserr_warn3sys("error: fsync: ", tmpfn.s, " - "); goto ERROR;
  }
  if (fchown(obuf.fd, uid, gid) == -1) {
    syserr_warn1sys("error: fchown: "); goto ERROR;
  }
  if (perm) {
    if (fchmod(obuf.fd, perm) == -1) {
      syserr_warn1sys("error: fchmod: "); goto ERROR;
    }
  }
  if (rename(tmpfn.s, to) == -1) {
    syserr_warn3sys("error: rename: ", to, " - "); goto ERROR;
  }
  if (close(ibuf.fd) == -1) syserr_warn1sys("error: close: ");
  if (close(obuf.fd) == -1) syserr_warn1sys("error: close: ");
  ibuf.fd = -1;
  obuf.fd = -1;

  return 1;

  ERROR:
  if (ibuf.fd != -1)
    if (close(ibuf.fd) == -1) syserr_warn1sys("error: close: ");
  ibuf.fd = -1;
  if (obuf.fd != -1) {
    if (unlink(tmpfn.s) == -1)
      if (errno != error_noent)
        syserr_warn3sys("error: unlink: ", tmpfn.s, " - ");
    if (close(obuf.fd) == -1) syserr_warn1sys("error: close: ");
  }
  obuf.fd = -1;
  return 0;
}
static int ntrans_link(const char **pfrom, const char **pto, const char *dir)
{
  if (!dir) { syserr_warn1x("error: directory not defined"); return 0; }
  if (!*pfrom) { syserr_warn1x("error: from file not defined"); return 0; }
  if (!*pto) { syserr_warn1x("error: to file not defined"); return 0; }
  return 1;
}
static int instop_link(struct install_item *ins, int uid, int gid,
                       unsigned int flag)
{
  const char *from;
  const char *to;
  const char *dir;
  unsigned int perm;
  int pwdfd;

  from = ins->from;
  to = ins->to;
  dir = ins->dir;
  perm = ins->perm;

  print_op("symlink", from, to, ins->owner, ins->group, perm);
  if (flag & INSTALL_DRYRUN) return 1;

  pwdfd = open_ro(".");
  if (pwdfd == -1) { syserr_warn1sys("error: open: "); return 0; }
  if (chdir(dir) == -1) { syserr_warn1sys("error: chdir: "); return 0; }
  if (unlink(to) == -1) {
    if (errno != error_noent) {
      syserr_warn3sys("error: symlink: ", to, " - "); goto ERROR;
    }
  }
  if (symlink(from, to) == -1) {
    syserr_warn3sys("error: symlink: ", to, " - "); goto ERROR;
  }
  if (fchdir(pwdfd) == -1) 
    syserr_die1sys(112, "fatal: could not restore current directory: ");
  if (close(pwdfd) == -1) syserr_warn1sys("error: close: ");
  return 1;
  ERROR:
  if (fchdir(pwdfd) == -1)
    syserr_die1sys(112, "fatal: could not restore current directory: ");
  if (close(pwdfd) == -1) syserr_warn1sys("error: close: ");
  return 0;
}
static int ntrans_liblink(const char **pfrom, const char **pto, const char *dir)
{
  const char *from;
  const char *to;
  int pos;

  from = *pfrom;
  to = *pto;
  
  if (!dir) { syserr_warn1x("error: directory not defined"); return 0; }
  if (!from) { syserr_warn1x("error: from file not defined"); return 0; }
  if (!to) to = from;
 
  sstr_trunc(&tmpfrom);
  sstr_trunc(&tmpto);
  if (str_ends(from, ".lib")) {
    if (!libname(from, tmpbuf)) return 0;
    from = tmpbuf;
  }
  if (!base_name(from, (char **) &from)) return 0;
  sstr_cats(&tmpfrom, from);

  pos = str_chr(from, '.') + 1;
  sstr_cats(&tmpto, "lib");
  sstr_catb(&tmpto, from, pos + scan_notcharset(from + pos, "."));

  sstr_0(&tmpfrom);
  sstr_0(&tmpto);
  from = tmpfrom.s;
  to = tmpto.s;

  *pfrom = from;
  *pto = to;
  return 1;
}
static int instop_liblink(struct install_item *ins, int uid, int gid,
                          unsigned int flag)
{
  return instop_link(ins, uid, gid, flag);
}
static int ntrans_mkdir(const char **pfrom, const char **pto, const char *dir)
{
  if (!dir) { syserr_warn1x("error: directory not defined"); return 0; }
  return 1;
}
static int instop_mkdir(struct install_item *ins, int uid, int gid,
                        unsigned int flag)
{
  unsigned int perm;
  int fd;
  const char *dir;

  perm = ins->perm;
  dir = ins->dir;
  print_op("mkdir", dir, 0, ins->owner, ins->group, perm);
  if (flag & INSTALL_DRYRUN) return 1;

  if (rmkdir(dir, ins->perm) == -1) {
    syserr_warn3sys("error: mkdir: ", dir, " - "); return 0;
  }
  fd = open_ro(dir);
  if (fd == -1) {
    syserr_warn3sys("error: open: ", dir, " - "); return 0;
  }
  if (fchown(fd, uid, gid) == -1) {
    syserr_warn3sys("error: fchown: ", dir, " - "); goto ERROR;
  }
  if (perm) { 
    if (fchmod(fd, perm) == -1) {
      syserr_warn3sys("error: fchmod: ", dir, " - "); goto ERROR;
    }
  }
  if (close(fd) == -1) syserr_warn3sys("error: close: ", dir, " - ");
  return 1;
  ERROR:
  if (close(fd) == -1) syserr_warn3sys("error: close: ", dir, " - ");
  return 0;
}

struct instop {
  int (*oper)(struct install_item *, int, int, unsigned int);
  int (*trans)(const char **, const char **, const char *);
};

static const struct instop install_opers[] = {
  { instop_copy, ntrans_copy },
  { instop_link, ntrans_link },
  { instop_mkdir, ntrans_mkdir },
  { instop_liblink, ntrans_liblink },
};
static const unsigned int num_inst_opers = sizeof(install_opers) /
                                           sizeof(struct instop);

static int instchk_file(struct install_item *ins, int uid, int gid,
                        unsigned int flag)
{
  int fd;
  int r;
  unsigned int perm;
  const char *to;

  to = ins->to;
  perm = ins->perm;

  print_op("check", 0, to, ins->owner, ins->group, perm);
  if (flag & INSTALL_DRYRUN) return 1; 

  fd = open_ro(to);
  if (fd == -1) {
    syserr_warn3sys("error: open: ", to, " - "); ++install_failed; return 0;
  }
  r = chkf(fd, to, uid, gid, perm, S_IFREG, "regular file");
  if (close(fd) == -1) syserr_warn3sys("error: close: ", to, " - ");
  return r;
}
static int instchk_link(struct install_item *ins, int uid, int gid,
                        unsigned int flag)
{
  unsigned int perm;
  const char *to;
  const char *dir;
  int r;
  int pwdfd;

  dir = ins->dir;
  to = ins->to;
  perm = ins->perm;

  print_op("check-link", 0, to, ins->owner, ins->group, perm);
  if (flag & INSTALL_DRYRUN) return 1; 
  pwdfd = open_ro(".");
  if (pwdfd == -1) { syserr_warn1sys("error: open: "); return 0; }
  if (chdir(dir) == -1) {
    syserr_warn3sys("error: chdir: ", dir, " - "); ++install_failed; return 0;
  }
  r = chkf(-1, to, uid, gid, perm, S_IFLNK, "symbolic link");
  if (!fchdir(pwdfd) == -1)
    syserr_die1sys(112, "fatal: could not restore current directory: ");
  if (close(pwdfd) == -1)
    syserr_warn1sys("error: close: ");
  return r;
}
static int instchk_dir(struct install_item *ins, int uid, int gid,
                       unsigned int flag)
{
  int r;
  int fd;
  unsigned int perm;
  const char *dir;

  dir = ins->dir;
  perm = ins->perm;

  print_op("check-dir", 0, dir, ins->owner, ins->group, ins->perm);
  if (flag & INSTALL_DRYRUN) return 1; 
  fd = open_ro(dir);
  if (fd == -1) {
    syserr_warn3sys("error: open: ", dir, " - "); ++install_failed; return 0;
  }
  r = chkf(fd, dir, uid, gid, perm, S_IFDIR, "directory");
  if (close(fd) == -1) syserr_warn3sys("error: close: ", dir, " - ");
  return r;
}
static int instchk_liblink(struct install_item *ins, int uid, int gid,
                           unsigned int flag)
{
  return instchk_link(ins, uid, gid, flag);
}

static const struct instop instchk_opers[] = {
  { instchk_file, ntrans_copy },
  { instchk_link, ntrans_link },
  { instchk_dir, ntrans_mkdir },
  { instchk_liblink, ntrans_liblink },
};
static const unsigned int num_instchk_opers = sizeof(instchk_opers) /
                                              sizeof(struct instop);

int install(struct install_item *i, unsigned int flag)
{
  int uid;
  int gid;

  if (i->op >= num_inst_opers) {
    syserr_warn1x("error: unknown operator");
    return 0;
  }
  if (!conv_uidgid(i->owner, &uid, i->group, &gid)) return 0;
  if (!install_opers[i->op].trans(&i->from, &i->to, i->dir)) return 0;
  return install_opers[i->op].oper(i, uid, gid, flag);
}
int install_check(struct install_item *i)
{
  int uid;
  int gid;

  if (i->op >= num_instchk_opers) {
    syserr_warn1x("error: unknown operator");
    return 0;
  }
  if (!conv_uidgid(i->owner, &uid, i->group, &gid)) return 0;
  if (!instchk_opers[i->op].trans(&i->from, &i->to, i->dir)) return 0;
  return instchk_opers[i->op].oper(i, uid, gid, 0);
}

static int deinst_file(struct install_item *ins, int uid, int gid,
                       unsigned int flag)
{
  print_op("unlink", 0, ins->to, 0, 0, 0);
  if (flag & INSTALL_DRYRUN) return 1; 

  if (unlink(ins->to) == -1) {
    syserr_warn3sys("error: unlink: ", ins->to, " - ");
    ++deinstall_failed;
    return 0;
  }
  return 1;
}
static int deinst_link(struct install_item *ins, int uid, int gid,
                       unsigned int flag)
{
  int pwdfd;

  print_op("unlink", 0, ins->to, 0, 0, 0);
  if (flag & INSTALL_DRYRUN) return 1; 

  pwdfd = open_ro(".");
  if (pwdfd == -1) { syserr_warn1sys("error: open: "); return 0; }
  if (chdir(ins->dir) == -1) {
    syserr_warn3sys("error: chdir: ", ins->dir, " - "); goto ERROR;
  }
  if (unlink(ins->to) == -1) {
    syserr_warn3sys("error: unlink: ", ins->to, " - "); goto ERROR;
  }
  if (fchdir(pwdfd) == -1)
    syserr_die1sys(112, "fatal: could not restore current directory: ");
  if (close(pwdfd) == -1) syserr_warn1sys("error: close: ");
  return 1;
  ERROR:
  ++deinstall_failed;
  if (fchdir(pwdfd) == -1)
    syserr_die1sys(112, "fatal: could not restore current directory: ");
  if (close(pwdfd) == -1) syserr_warn1sys("error: close: ");
  return 0;
}
static int deinst_dir(struct install_item *ins, int uid, int gid,
                      unsigned int flag)
{
  print_op("rmdir", 0, ins->dir, 0, 0, 0);
  if (flag & INSTALL_DRYRUN) return 1; 

  if (rmdir(ins->dir) == -1) {
    syserr_warn3sys("error: rmdir: ", ins->dir, " - ");
    ++deinstall_failed;
    return 0;
  }
  return 1;
}
static int deinst_liblink(struct install_item *ins, int uid, int gid,
                          unsigned int flag)
{
  return deinst_link(ins, uid, gid, flag);
}

static const struct instop deinst_opers[] = {
  { deinst_file, ntrans_copy },
  { deinst_link, ntrans_link },
  { deinst_dir, ntrans_mkdir },
  { deinst_liblink, ntrans_liblink },
};
static const unsigned int num_deinst_opers = sizeof(deinst_opers) /
                                             sizeof(struct instop);

int deinstall(struct install_item *i, unsigned int flag)
{
  int uid;
  int gid;

  if (i->op >= num_deinst_opers) {
    syserr_warn1x("error: unknown operator");
    return 0;
  }
  if (!conv_uidgid(i->owner, &uid, i->group, &gid)) return 0;
  if (!deinst_opers[i->op].trans(&i->from, &i->to, i->dir)) return 0;
  return deinst_opers[i->op].oper(i, uid, gid, 0);
}
