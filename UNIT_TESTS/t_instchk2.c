#include <sys/stat.h>
#include <string.h>
#include <stdio.h>

#define INSTALL_IMPLEMENTATION
#include "../install.h"

const char progname[] = "t_instchk2";

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
  unsigned long index;
  unsigned int mask;
  int return_code;
  struct install_status_t status;

  mask = install_umask (022);
  return_code = 0;

  status = install_init ("conf-sosuffix");
  if (status.status != INSTALL_STATUS_OK) {
    printf ("%s: init: %s - %s\n", progname, status.message, status.error_message);
    return 1;
  }

  install_callback_warn_set (cb_warn);
  install_callback_info_set (cb_info);

  for (index = 0; index < insthier_len; ++index) {
    status = install_check (&insthier [index]);
    if (status.status != INSTALL_STATUS_OK) {
      printf ("%s: check %lu failed: %s - %s\n", progname, index,
        status.message, status.error_message);
      return_code = 1;
    }
  }

  fflush (0);
  install_umask (mask);
  return return_code;
}
