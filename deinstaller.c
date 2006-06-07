#include <sys/stat.h>
#include "buffer.h"
#include "get_opt.h"
#include "fmt.h"
#include "install.h"
#include "syserr.h"

const char progname[] = "deinstall";

int main(int argc, char **argv)
{
  char cnum[FMT_ULONG];
  unsigned int flags;
  unsigned int ind;
  char ch;

  flags = 0;
  while ((ch = get_opt(argc, argv, "n")) != opteof)
    switch (ch) {
      case 'n': flags |= INSTALL_DRYRUN; break;
      default: return 111; break;
    }

  for (ind = insthier_size - 1;; --ind) {
    deinstall(&insthier[ind], flags);    
    if (!ind) break;
  }

  if (deinstall_failed) {
    cnum[fmt_uint(cnum, deinstall_failed)] = 0;
    buffer_puts(buffer1, cnum);
    buffer_puts(buffer1, " of ");
    cnum[fmt_uint(cnum, insthier_size)] = 0;
    buffer_puts(buffer1, cnum);
    buffer_puts(buffer1, " files failed to deinstall\n");
  }

  if (buffer_flush(buffer1) == -1) syserr_die1sys(112, "fatal: write: ");
  return 0;
}
