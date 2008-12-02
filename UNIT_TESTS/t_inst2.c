#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include "../install.h"

const char progname[] = "t_inst2";

int
main (void)
{
  unsigned long i;
  unsigned int um;
  int tret;
  struct install_status_t status;

  um = install_umask (022);
  tret = 0;

  if (!install_init ()) return 112;

  printf("installing...\n");
  for (i = 0; i < insthier_len; ++i) {
    status = install (&insthier[i], 0);
    if (status.status != INSTALL_STATUS_OK) {
      printf ("install %lu failed\n", i);
      tret = 1;
    }
  }

  fflush (0);
  install_umask (um);
  return tret;
}
