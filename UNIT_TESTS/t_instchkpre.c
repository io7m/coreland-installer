#include <sys/stat.h>
#include <stdio.h>
#include "../install.h"

const char progname[] = "t_instchkpre";

int
main (void)
{
  unsigned long i;
  unsigned int um;
  struct install_status_t status;

  um = install_umask (022);

  if (!install_init ()) return 112;

  for (i = 0; i < insthier_len; ++i) {
    status = install_check (&insthier[i]);
    if (status.status != INSTALL_STATUS_ERROR) {
      printf("install_check[%lu] returned %d expected %d\n", i, status.status,
        INSTALL_STATUS_ERROR);
      install_umask (um);
      return 1;
    }
  }

  install_umask (um);
  return 0;
}
