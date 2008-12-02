#include <stdio.h>
#include "../install.h"

const char progname[] = "t_deinst12";

int
main (void)
{
  unsigned long i;
  struct install_status_t status;

  if (!install_init ()) return 112;

  for (i = insthier_len - 1;; --i) {
    status = deinstall (&insthier[i], 0);
    if (status.status != INSTALL_STATUS_ERROR) {
      printf("deinstall[%lu] returned %d expected %d\n", i, status.status,
        INSTALL_STATUS_ERROR);
      return 1;
    }
    if (i == 0) break;
  }

  return 0;
}
