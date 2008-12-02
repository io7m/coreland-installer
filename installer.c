#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "install.h"

const char progname[] = "installer";

int
main (int argc, char *argv[])
{
  unsigned long i;
  unsigned int flag;
  struct install_status_t status;

  argv = 0;
  if (!install_init ()) return 112;

  flag = (argc > 1) ? INSTALL_DRYRUN : 0;
  for (i = 0; i < insthier_len; ++i) {
    status = install (&insthier[i], flag);
    switch (status.status) {
      case INSTALL_STATUS_OK:
        break;
      case INSTALL_STATUS_ERROR:
        printf ("installer: error: %s - %s\n", status.message, install_error (errno));
        break;
      case INSTALL_STATUS_FATAL:
        printf ("installer: fatal: %s - %s\n", status.message, install_error (errno));
        exit (112);
        break;
    }
  }

  return 0;
}
