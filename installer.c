#include <sys/stat.h>
#include "buffer.h"
#include "get_opt.h"
#include "install.h"
#include "syserr.h"

const char progname[] = "install";

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
