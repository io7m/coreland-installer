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
#include "sstring.h"
#include "syserr.h"
#include "write.h"
#include "uint64.h"

extern const struct install_item insthier[];
extern const unsigned int insthier_size;

static char fbuf[1024];
static sstring file = sstring_INIT(fbuf);
static int install_ok = 1;

const char progname[] = "instchk";

int install_check(const struct install_item *it)
{
  char cnum[FMT_UINT64ANY];
  char cnum2[FMT_UINT64ANY];
  uint64 uid;
  uint64 gid;
  struct stat sb;
  struct group *grp;
  struct passwd *pwd;
  int fd;

  if (!it->home) return 0;

  buffer_puts(buffer1, "check ");
  buffer_puts(buffer1, it->home);

  if (it->file) {
    buffer_puts(buffer1, "/");
    buffer_puts(buffer1, it->file);
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

  sstring_trunc(&file);
  sstring_cats(&file, it->home);
  if (it->file) {
    sstring_cats(&file, "/");
    sstring_cats(&file, it->file);
  }
  sstring_0(&file);

  fd = open_ro(file.s);
  if (fd == -1) {
    install_ok = 0; syserr_warn3sys("error: open: ", file.s, " - "); return 0;
  }
  /* fstat failing is unlikely to be an install error */
  if (fstat(fd, &sb)) {
    syserr_warn3sys("error: fstat: ", file.s, " - "); goto ERR;
  }

  if (uid != sb.st_uid) {
    cnum[fmt_u64o(cnum, sb.st_uid)] = 0;
    cnum2[fmt_u64o(cnum2, uid)] = 0;
    syserr_warn4x("error: file uid ", cnum, " does not match expected uid ", cnum2);
    install_ok = 0;
    goto ERR;
  }
  if (gid != sb.st_gid) {
    cnum[fmt_u64o(cnum, sb.st_gid)] = 0;
    cnum2[fmt_u64o(cnum2, gid)] = 0;
    syserr_warn4x("error: file gid ", cnum, " does not match expected gid ", cnum2);
    install_ok = 0;
    goto ERR;
  }

  if (it->file) {
    if ((sb.st_mode & S_IFMT) != S_IFREG) {
      syserr_warn3x("error: ", file.s, " is not a regular file");
      install_ok = 0;
      goto ERR;
    }
  } else {
    if ((sb.st_mode & S_IFMT) != S_IFDIR) {
      syserr_warn3x("error: ", file.s, " is not a directory");
      install_ok = 0;
      goto ERR;
    }
  }

  if ((uint64) (sb.st_mode & 07777) != it->perm) {
    cnum[fmt_u64o(cnum, sb.st_mode & 07777)] = 0;
    cnum2[fmt_u64o(cnum2, it->perm)] = 0;
    syserr_warn4x("error: file mode ", cnum, " does not match expected mode ", cnum2);
    install_ok = 0;
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

int main()
{
  unsigned int ind;

  for (ind = 0; ind < insthier_size; ++ind)
    install_check(&insthier[ind]);    

  if (!install_ok)
    buffer_puts(buffer1, "One or more files were incorrectly installed.\n");
  else
    buffer_puts(buffer1, "All files were correctly installed.\n");

  if (buffer_flush(buffer1) == -1) syserr_die1sys(112, "fatal: write: ");
  return 0;
}
