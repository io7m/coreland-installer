#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "install.h"

const char progname[] = "deinstaller";

int
main (int argc, char *argv[])
{
  unsigned long i;
  unsigned int flag;
  struct install_status_t status;

  argv = 0;
  if (!install_init ()) return 112;

  flag = (argc > 1) ? INSTALL_DRYRUN : 0;
  for (i = insthier_len - 1;; --i) {
    status = deinstall (&insthier[i], flag);
    switch (status.status) {
      case INSTALL_STATUS_OK:
        break;
      case INSTALL_STATUS_ERROR:
        printf ("deinstaller: error: %s - %s\n", status.message, install_error (errno));
        break;
      case INSTALL_STATUS_FATAL:
        printf ("deinstaller: fatal: %s - %s\n", status.message, install_error (errno));
        exit (112);
        break;
    }
    if (i == 0) break;
  }

  return 0;
}
