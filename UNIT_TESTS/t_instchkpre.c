#include <sys/stat.h>
#include <stdio.h>
#include "../install.h"

const char progname[] = "t_instchkpre";

int main()
{
  unsigned long i;
  unsigned int um;
  int ret;

  um = install_umask (022);

  if (!install_init ()) return 112;

  for (i = 0; i < insthier_len; ++i) {
    ret = install_check (&insthier[i]);
    if (ret != 0) {
      printf("install_check[%lu] returned %d expected %d\n", i, ret, 0);
      install_umask (um);
      return 1;
    }
  }

  install_umask (um);
  return 0;
}
