#include <sys/stat.h>
#include <stdio.h>
#include "../install.h"

const char progname[] = "t_inst1";

extern unsigned int return_codes[5];

int
main (void)
{
  unsigned long index;
  unsigned int um;
  struct install_status_t status;

  um = install_umask (022);

  status = install_init ();
  if (status.status != INSTALL_STATUS_OK) {
    printf ("install: init: %s\n", status.message);
    return 1;
  }

  for (index = 0; index < insthier_len; ++index) {
    status = install (&insthier [index], 0);
    if (return_codes [index] != status.status) {
      printf ("install [%lu] returned %d expected %d\n", index,
        status.status, return_codes [index]);
      install_umask (um);
      return 1;
    }
  }

  install_umask (um);
  return 0;
}
