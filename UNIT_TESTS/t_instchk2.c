#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include "../install.h"

const char progname[] = "t_instchk2";

int
main (void)
{
  unsigned long i;
  unsigned int um;
  int tret;
  struct install_status_t status;

  um = install_umask (022);
  tret = 0;

  status = install_init ();
  if (status.status != INSTALL_STATUS_OK) {
    printf ("check: init: %s\n", status.message);
    return 1;
  }

  printf("checking...\n");
  for (i = 0; i < insthier_len; ++i) {
    status = install_check (&insthier[i]);
    if (status.status != INSTALL_STATUS_OK) tret = 1;
  }

  fflush (0);
  install_umask (um);
  return tret;
}
