#include <stdio.h>
#include "../install.h"

const char progname[] = "t_deinst12";

int
main (void)
{
  unsigned long index;
  struct install_status_t status;

  if (!install_init ()) return 112;

  for (index = insthier_len - 1;; --index) {
    status = deinstall (&insthier[index], 0);
    if (status.status != INSTALL_STATUS_ERROR) {
      printf("deinstall [%lu] returned %d expected %d\n", index,
        status.status, INSTALL_STATUS_ERROR);
      return 1;
    }
    printf ("deinstall: %s\n", status.message);
    if (index == 0) break;
  }

  return 0;
}
