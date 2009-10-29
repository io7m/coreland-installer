#include <stdio.h>

#define INSTALL_IMPLEMENTATION
#include "../install.h"

const char progname[] = "t_deinst12";

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
  struct install_status_t status;

  status = install_init ("conf-sosuffix");
  if (status.status != INSTALL_STATUS_OK) {
    printf ("deinstall: init: %s\n", status.message);
    return 1;
  }

  install_callback_warn_set (cb_warn);
  install_callback_info_set (cb_info);

  for (index = insthier_len - 1;; --index) {
    status = deinstall (&insthier[index], 0);
    if (status.status != INSTALL_STATUS_ERROR) {
      printf("deinstall [%lu] returned %d expected %d\n", index,
        status.status, INSTALL_STATUS_ERROR);
      return 1;
    }
    printf ("deinstall: %s - %s\n", status.message, status.error_message);
    if (index == 0) break;
  }

  return 0;
}
