#include <sys/stat.h>
#include <stdio.h>

#define INSTALL_IMPLEMENTATION
#include "../install.h"

const char progname[] = "t_instchk1";

extern unsigned int return_codes[5];

void
cb_info (const char *str, void *data)
{
  printf ("%s: %s\n", progname, str);
}

void
cb_warn (const char *str, void *data)
{
  printf ("%s: %s\n", progname, str);
}

int
main (void)
{
  unsigned long i;
  unsigned int um;
  struct install_status_t status;

  um = install_umask (022);

  status = install_init ("conf-sosuffix");
  if (status.status != INSTALL_STATUS_OK) {
    printf ("install: init: %s\n", status.message);
    return 1;
  }

  install_callback_warn_set (cb_warn);
  install_callback_info_set (cb_info);

  for (i = 0; i < insthier_len; ++i) {
    status = install_check (&insthier[i]);
    if (status.status != return_codes[i]) {
      printf("install_check[%lu] returned %d expected %d\n", i, status.status,
        return_codes[i]);
      if (status.message)
        printf ("install_check: %s - %s\n", status.message, status.error_message);
      install_umask (um);
      return 1;
    }
  }

  install_umask (um);
  return 0;
}
