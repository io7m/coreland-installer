#include <sys/stat.h>
#include <stdio.h>

#define INSTALL_IMPLEMENTATION
#include "../install.h"

const char progname[] = "t_instchkpre";

void
cb_info (const char *str, void *data)
{
  printf ("%s\n", str);
}

void
cb_warn (const char *str, void *data)
{
  printf ("%s\n", str);
}

int
main (void)
{
  unsigned long i;
  unsigned int um;
  struct install_status_t status;

  um = install_umask (022);

  status = install_init ();
  if (status.status != INSTALL_STATUS_OK) {
    printf ("install_check: init: %s\n", status.message);
    return 1;
  }

  install_callback_warn_set (cb_warn);
  install_callback_info_set (cb_info);

  for (i = 0; i < insthier_len; ++i) {
    status = install_check (&insthier[i]);
    if (status.status != INSTALL_STATUS_ERROR) {
      printf("install_check [%lu] returned %d expected %d\n", i, status.status,
        INSTALL_STATUS_ERROR);
      install_umask (um);
      return 1;
    }
    printf ("install_check: %s\n", status.message);
  }

  install_umask (um);
  return 0;
}
