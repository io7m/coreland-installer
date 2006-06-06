#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include "buffer.h"
#include "error.h"
#include "fmt.h"
#include "install.h"
#include "open.h"
#include "read.h"
#include "str.h"
#include "sstring.h"
#include "syserr.h"
#include "write.h"

extern const struct install_item insthier[];
extern const unsigned int insthier_size;

static char fbuf1[1024];
static char fbuf2[1024];
static sstring file1 = sstring_INIT(fbuf1);
static sstring file2 = sstring_INIT(fbuf2);

unsigned int install_failed = 0;

int install_check(const struct install_item *it)
{
  char cnum[FMT_ULONG];
  char cnum2[FMT_ULONG];
  unsigned int uid;
  unsigned int gid;
  struct stat sb;
  struct group *grp;
  struct passwd *pwd;
  int fd;

  if (!it->dir) {
    syserr_warn1x("error: directory undefined");
    ++install_failed;
    return 0;
  }

  buffer_puts(buffer1, "check ");
  buffer_puts(buffer1, it->dir);

  sstring_trunc(&file2);

  if (it->to) {
    if (it->from)
      sstring_cats(&file2, it->from);
    else
      sstring_cats(&file2, it->to);
    sstring_0(&file2);
    if (str_ends(file2.s, ".lib"))
      if (!install_libname(&file2)) return 0;
    buffer_puts(buffer1, "/");
    buffer_puts(buffer1, file2.s);
  }

  buffer_puts(buffer1, " ");
  cnum[fmt_uinto(cnum, it->perm)] = 0;
  buffer_puts(buffer1, cnum);
  buffer_puts(buffer1, " ");
  buffer_puts(buffer1, it->owner);
  buffer_puts(buffer1, ":");
  buffer_puts(buffer1, it->group);
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

  sstring_trunc(&file1);
  sstring_cats(&file1, it->dir);
  if (file2.len) {
    sstring_cats(&file1, "/");
    sstring_cats(&file1, file2.s);
  }
  sstring_0(&file1);

  fd = open_ro(file1.s);
  if (fd == -1) {
    ++install_failed; syserr_warn3sys("error: open: ", file1.s, " - "); return 0;
  }
  /* fstat failing is unlikely to be an install error */
  if (fstat(fd, &sb)) {
    syserr_warn3sys("error: fstat: ", file1.s, " - "); goto ERR;
  }

  if (uid != sb.st_uid) {
    cnum[fmt_ulongo(cnum, sb.st_uid)] = 0;
    cnum2[fmt_ulongo(cnum2, uid)] = 0;
    syserr_warn4x("error: file uid ", cnum, " does not match expected uid ", cnum2);
    ++install_failed;
    goto ERR;
  }
  if (gid != sb.st_gid) {
    cnum[fmt_ulongo(cnum, sb.st_gid)] = 0;
    cnum2[fmt_ulongo(cnum2, gid)] = 0;
    syserr_warn4x("error: file gid ", cnum, " does not match expected gid ", cnum2);
    ++install_failed;
    goto ERR;
  }

  if (it->to) {
    if ((sb.st_mode & S_IFMT) != S_IFREG) {
      syserr_warn3x("error: ", file1.s, " is not a regular file");
      ++install_failed;
      goto ERR;
    }
  } else {
    if ((sb.st_mode & S_IFMT) != S_IFDIR) {
      syserr_warn3x("error: ", file1.s, " is not a directory");
      ++install_failed;
      goto ERR;
    }
  }

  if ((sb.st_mode & 07777) != it->perm) {
    cnum[fmt_ulongo(cnum, sb.st_mode & 07777)] = 0;
    cnum2[fmt_ulongo(cnum2, it->perm)] = 0;
    syserr_warn4x("error: file mode ", cnum, " does not match expected mode ", cnum2);
    ++install_failed;
    goto ERR;
  }

  if (close(fd) == -1) syserr_warn1sys("error: close: ");
  fd = -1;
  return 1;

  ERR:

  if (fd != -1)
    if (close(fd) == -1) syserr_warn1sys("error: close: ");
  fd = -1;
  return 0;
}
