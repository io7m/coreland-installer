#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "install.h"

const char progname[] = "instchk";

int
main (void)
{
  unsigned long i;
  struct install_status_t status;

  status = install_init ();
  if (status.status != INSTALL_STATUS_OK) {
    printf ("instchk: init: %s - %s\n", status.message, install_error (errno));
    exit (112);
  }

  for (i = 0; i < insthier_len; ++i) {
    status = install_check (&insthier[i]);
    switch (status.status) {
      case INSTALL_STATUS_OK:
        break;
      case INSTALL_STATUS_ERROR:
        printf ("instchk: error: %s - %s\n", status.message, install_error (errno));
        break;
      case INSTALL_STATUS_FATAL:
        printf ("instchk: fatal: %s - %s\n", status.message, install_error (errno));
        exit (112);
        break;
    }
  }

  if (install_failed) {
    printf ("instchk: %lu of %lu files failed\n", install_failed, insthier_len);
    return 1;
  }
  return 0;
}
