#include "install.h"

const char progname[] = "installer";

int main(int argc, char *argv[])
{
  unsigned long i;
  unsigned int flag;

  if (!check_tools()) return 112;

  if (argc > 1)
    flag = INSTALL_DRYRUN;
  else
    flag = 0;

  for (i = 0; i < insthier_len; ++i)
    install(&insthier[i], flag);

  return 0;
}
