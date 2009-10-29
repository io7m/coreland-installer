#include <sys/stat.h>
#include <stdio.h>

#define INSTALL_IMPLEMENTATION
#include "../install.h"

const char progname[] = "t_inst3";

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
  unsigned long index;
  unsigned int um;
  struct install_status_t status;

  um = install_umask (022);

  install_fake_root ("installto/t3/fake_root");

  status = install_init ("conf-sosuffix");
  if (status.status != INSTALL_STATUS_OK) {
    printf ("install: init: %s\n", status.message);
    return 1;
  }

  install_callback_warn_set (cb_warn);
  install_callback_info_set (cb_info);

  for (index = 0; index < insthier_len; ++index) {
    status = install (&insthier [index], 0);
    if (return_codes [index] != status.status) {
      printf ("install [%lu] returned %d expected %d\n", index,
        status.status, return_codes [index]);
      if (status.message)
        printf ("install: %s - %s\n", status.message, status.error_message);
      install_umask (um);
      return 1;
    }
    if (status.message)
      printf ("install: %s - %s\n", status.message, status.error_message);
  }

  install_umask (um);
  return 0;
}
