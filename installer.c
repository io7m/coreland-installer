#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include "buffer.h"
#include "error.h"
#include "fmt.h"
#include "fsync.h"
#include "get_opt.h"
#include "install.h"
#include "open.h"
#include "read.h"
#include "sstring.h"
#include "syserr.h"
#include "write.h"
#include "uint64.h"

extern int rename(const char *, const char *);

extern const struct install_item insthier[];
extern const unsigned int insthier_size;

static char fbuf3[1024];
static char fbuf2[1024];
static char fbuf1[1024];
static sstring file1 = sstring_INIT(fbuf1);
static sstring file2 = sstring_INIT(fbuf2);
static sstring tmpfile = sstring_INIT(fbuf3);

static char bbuf1[4096];
static char bbuf2[4096];
static buffer bin = buffer_INIT(read, -1, bbuf1, sizeof(bbuf1));
static buffer bout = buffer_INIT(write, -1, bbuf2, sizeof(bbuf2));

const char progname[] = "install";

static int copy(const char *from, const char *to, uint64 uid, uint64 gid,
                unsigned int perm)
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

int install(const struct install_item *it, unsigned int flags)
{
  char cnum[FMT_UINT64ANY];
  uint64 uid;
  uint64 gid;
  struct group *grp;
  struct passwd *pwd;

  sstring_trunc(&file2);

  if (it->file) {
    sstring_cats(&file2, it->file);
    sstring_0(&file2);
    if (str_ends(it->file, ".lib"))
      if (!install_libname(&file2)) return 0;
    buffer_puts(buffer1, "install ");
    buffer_puts(buffer1, file2.s);
    buffer_puts(buffer1, " ");
  } else {
    buffer_puts(buffer1, "mkdir ");
  }

  buffer_puts(buffer1, it->home);

  if (file2.len) {
    buffer_puts(buffer1, "/");
    buffer_puts(buffer1, file2.s);
  }

  buffer_puts(buffer1, " ");
  buffer_puts(buffer1, it->owner);
  buffer_puts(buffer1, ":");
  buffer_puts(buffer1, it->group);
  buffer_puts(buffer1, " ");
  cnum[fmt_u64o(cnum, (uint64) it->perm)] = 0;
  buffer_puts(buffer1, cnum);
  buffer_puts(buffer1, "\n");
  buffer_flush(buffer1);

  errno = 0;
  pwd = getpwnam(it->owner);
  if (!pwd) {
    if (errno) {
      syserr_warn1sys("error: getpwnam: "); return 0;
    } else {
      syserr_warn3x("error: no such user '", it->owner, "'"); return 0;
    }
  }
  uid = pwd->pw_uid;

  errno = 0;
  grp = getgrnam(it->group);
  if (!pwd) {
    if (errno) {
      syserr_warn1sys("error: getgrnam: "); return 0;
    } else {
      syserr_warn3x("error: no such group '", it->group, "'"); return 0;
    }
  }
  gid = grp->gr_gid;

  if (flags & INSTALL_DRYRUN) return 1;

  sstring_trunc(&file1);
  sstring_cats(&file1, it->home);

  if (file2.len) {
    sstring_cats(&file1, "/");
    sstring_cats(&file1, file2.s);
    sstring_0(&file1);
    return copy(file2.s, file1.s, uid, gid, it->perm);
  } else {
    if (mkdir(it->home, it->perm) == -1) {
      syserr_warn3sys("error: mkdir: ", it->home, " - "); return 0;
    }
    if (chown(it->home, uid, gid) == -1) {
      syserr_warn3sys("error: chown: ", it->home, " - "); return 0;
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
