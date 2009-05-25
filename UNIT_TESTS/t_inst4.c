#include <sys/stat.h>
#include <string.h>
#include <stdio.h>

#define INSTALL_IMPLEMENTATION
#include "../install.h"

const char progname[] = "t_inst4";

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
  int tret;
  struct install_status_t status;

  install_fake_root ("installto/t4/fake_root");

  um = install_umask (022);
  tret = 0;

  status = install_init ("conf-sosuffix");
  if (status.status != INSTALL_STATUS_OK) {
    printf ("install: init: %s\n", status.message);
    return 1;
  }

  install_callback_warn_set (cb_warn);
  install_callback_info_set (cb_info);

  printf("installing...\n");
  for (i = 0; i < insthier_len; ++i) {
    status = install (&insthier[i], 0);
    if (status.status != INSTALL_STATUS_OK) {
      printf ("install %lu failed\n", i);
      tret = 1;
    }
  }

  fflush (0);
  install_umask (um);
  return tret;
}
