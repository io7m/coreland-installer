#include <sys/stat.h>
#include "buffer.h"
#include "get_opt.h"
#include "install.h"
#include "syserr.h"

extern const struct install_item insthier[];
extern const unsigned int insthier_size;

const char progname[] = "deinstall";

int main(int argc, char **argv)
{
  char ch;
  unsigned int flags;
  unsigned int ind;

  flags = 0;
  while ((ch = get_opt(argc, argv, "n")) != opteof)
    switch (ch) {
      case 'n': flags |= DEINSTALL_DRYRUN; break;
      default: return 111; break;
    }

  for (ind = insthier_size - 1;; --ind) {
    deinstall(&insthier[ind], flags);    
    if (!ind) break;
  }

  if (buffer_flush(buffer1) == -1) syserr_die1sys(112, "fatal: write: ");
  return 0;
}
