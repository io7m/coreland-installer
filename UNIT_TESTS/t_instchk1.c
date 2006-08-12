#include <sys/stat.h>
#include "../install.h"

const char progname[] = "t_inst1";

int main()
{
  unsigned long i;
  unsigned int um;

  um = umask(022);

  if (!check_tools()) return 112;

  for (i = 0; i < insthier_len; ++i)
    install_check(&insthier[i]);

  umask(um);
  return 0;
}
