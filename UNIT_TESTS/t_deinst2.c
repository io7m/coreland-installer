#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include "../install.h"

const char progname[] = "t_deinst2";

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

  printf("deinstalling...\n");
  for (i = insthier_len - 1;; --i) {
    status = deinstall (&insthier[i], 0);
    if (status.status != INSTALL_STATUS_OK) tret = 1;
    if (i == 0) break;
  }

  fflush(0);
  install_umask (um);
  return tret;
}
