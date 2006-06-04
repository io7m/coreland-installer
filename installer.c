#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include "buffer.h"
#include "error.h"
#include "fmt.h"
#include "get_opt.h"
#include "install.h"
#include "open.h"
#include "read.h"
#include "rmkdir.h"
#include "str.h"
#include "sstring.h"
#include "syserr.h"
#include "write.h"

extern int rename(const char *, const char *);
extern int fsync(int);

extern const struct install_item insthier[];
extern const unsigned int insthier_size;

static char fbuf3[1024];
static char fbuf2[1024];
static char fbuf1[1024];
static sstring filefrom = sstring_INIT(fbuf1);
static sstring fileto = sstring_INIT(fbuf2);
static sstring tmpfile = sstring_INIT(fbuf3);

static char bbuf1[4096];
static char bbuf2[4096];
static buffer bin = buffer_INIT(read, -1, bbuf1, sizeof(bbuf1));
static buffer bout = buffer_INIT(write, -1, bbuf2, sizeof(bbuf2));

const char progname[] = "install";

static int copy(const char *from, const char *to,
                unsigned int uid, unsigned int gid, unsigned int perm)
{
  char *s;
  int r;
  int w;

  sstring_trunc(&tmpfile);
  sstring_cats(&tmpfile, to);
  sstring_cats(&tmpfile, ".tmp");
  sstring_0(&tmpfile);
 
  bin.fd = open_ro(from);
  if (bin.fd == -1) { syserr_warn3sys("error: open: ", from, " "); goto ERR; }
  bout.fd = open_trunc(tmpfile.s);
  if (bout.fd == -1) { syserr_warn3sys("error: open: ", tmpfile.s, " "); goto ERR; }

  for (;;) {
    r = buffer_feed(&bin);
    if (r == 0) break;
    if (r == -1) { syserr_warn1sys("error: read: "); goto ERR; }
    s = buffer_peek(&bin);
    w = buffer_put(&bout, s, r);
    if (w == -1) { syserr_warn1sys("error: write: "); goto ERR; }
    buffer_seek(&bin, r);
  }

  if (buffer_flush(&bout) == -1) { syserr_warn1sys("error: write: "); goto ERR; }
  if (fsync(bout.fd) == -1) { syserr_warn1sys("error: fsync: "); goto ERR; }
  if (fchmod(bout.fd, perm)) { syserr_warn1sys("error: fchmod: "); goto ERR; }
  if (fchown(bout.fd, uid, gid)) { syserr_warn1sys("error: fchown: "); goto ERR; }
  if (rename(tmpfile.s, to)) { syserr_warn1sys("error: rename: "); goto ERR; }
  if (close(bin.fd) == -1) syserr_warn1sys("error: close: ");
  if (close(bout.fd) == -1) syserr_warn1sys("error: close: ");
  bin.fd = -1;
  bout.fd = -1;

  return 1;

  ERR:
  if (bin.fd != -1)
    if (close(bin.fd) == -1) syserr_warn1sys("error: close: ");
  bin.fd = -1;
  if (bout.fd != -1) {
    if (unlink(tmpfile.s) == -1)
      if (errno != error_noent)
        syserr_warn3sys("error: unlink: ", tmpfile.s, " - ");
    if (close(bout.fd) == -1) syserr_warn1sys("error: close: ");
  }
  bout.fd = -1;
  return 0;
}

int install(const struct install_item *inst, unsigned int flags)
{
  char cnum[FMT_ULONG];
  unsigned int uid;
  unsigned int gid;
  struct group *grp;
  struct passwd *pwd;
  const char *from;

  sstring_trunc(&filefrom);
  sstring_trunc(&fileto);
  sstring_trunc(&tmpfile);

  if (!inst->dir) { syserr_warn1x("error: directory undefined"); return 0; }

  if (inst->to) {
    if (inst->from)
      from = inst->from;
    else
      from = inst->to;

    sstring_cats(&tmpfile, inst->to);
    sstring_0(&tmpfile);
    if (str_ends(tmpfile.s, ".lib"))
      if (install_libname(&tmpfile)) return 0;
    sstring_cats(&fileto, inst->dir);
    sstring_cats(&fileto, "/");
    sstring_cats(&fileto, tmpfile.s);
    sstring_0(&fileto);

    sstring_trunc(&tmpfile);
    sstring_cats(&tmpfile, from);
    sstring_0(&tmpfile);
    if (str_ends(tmpfile.s, ".lib"))
      if (install_libname(&tmpfile)) return 0;
    sstring_cats(&filefrom, tmpfile.s);
    sstring_0(&filefrom);
 
    buffer_puts(buffer1, "install ");
    buffer_puts(buffer1, filefrom.s);
    buffer_puts(buffer1, " ");
    buffer_puts(buffer1, fileto.s);
    buffer_puts(buffer1, " ");
  } else {
    buffer_puts(buffer1, "mkdir ");
    buffer_puts(buffer1, inst->dir);
    buffer_puts(buffer1, " ");
  }

  cnum[fmt_uinto(cnum, inst->perm)] = 0;
  buffer_puts(buffer1, cnum);
  buffer_puts(buffer1, " ");
  buffer_puts(buffer1, inst->owner);
  buffer_puts(buffer1, ":");
  buffer_puts(buffer1, inst->group);
  buffer_puts(buffer1, "\n");
  if (buffer_flush(buffer1)) syserr_warn1sys("warn: write: ");

  errno = 0;
  pwd = getpwnam(inst->owner);
  if (!pwd) {
    if (errno) {
      syserr_warn1sys("error: getpwnam: "); return 0;
    } else {
      syserr_warn3x("error: no such user '", inst->owner, "'"); return 0;
    }
  }
  uid = pwd->pw_uid;

  errno = 0;
  grp = getgrnam(inst->group);
  if (!pwd) {
    if (errno) {
      syserr_warn1sys("error: getgrnam: "); return 0;
    } else {
      syserr_warn3x("error: no such group '", inst->group, "'"); return 0;
    }
  }
  gid = grp->gr_gid;

  if (flags & INSTALL_DRYRUN) return 1;

  if (fileto.len) {
    return copy(filefrom.s, fileto.s, uid, gid, inst->perm);
  } else {
    if (rmkdir(inst->dir, inst->perm) == -1)
      if (errno != error_exist) {
        syserr_warn3sys("error: mkdir: ", inst->dir, " - "); return 0;
      }
    if (chown(inst->dir, uid, gid) == -1) {
      syserr_warn3sys("error: chown: ", inst->dir, " - "); return 0;
    }
    return 1;
  }
}

int main(int argc, char **argv)
{
  char ch;
  unsigned int flags;
  unsigned int ind;
  unsigned int mode;

  mode = umask(022);
  flags = 0;
  while ((ch = get_opt(argc, argv, "n")) != opteof)
    switch (ch) {
      case 'n': flags |= INSTALL_DRYRUN; break;
      default: return 111; break;
    }

  for (ind = 0; ind < insthier_size; ++ind)
    install(&insthier[ind], flags);    

  umask(mode);
  if (buffer_flush(buffer1) == -1) syserr_die1sys(112, "fatal: write: ");
  return 0;
}
