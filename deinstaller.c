#include "install.h"

const char progname[] = "deinstaller";

int main(int argc, char *argv[])
{
  unsigned long i;
  unsigned int flag;

  if (!check_tools()) return 112;

  if (argc > 1)
    flag = INSTALL_DRYRUN;
  else
    flag = 0;

  for (i = insthier_len - 1;; --i) {
    deinstall(&insthier[i], flag);
    if (i == 0) break;
  }

  return 0;
}
