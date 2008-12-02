#include <stdio.h>
#include "../install.h"

const char progname[] = "t_deinst1";

extern unsigned int return_codes[5];

int
main (void)
{
  unsigned long index;
  struct install_status_t status;

  if (!install_init ()) return 112;

  for (index = insthier_len - 1;; --index) {
    status = deinstall (&insthier [index], 0);
    if (return_codes [index] != status.status) {
      printf ("deinstall [%lu] returned %d expected %d\n", index,
        status.status, return_codes [index]);
      printf ("deinstall: %s\n", status.message);
      return 1;
    }
    if (index == 0) break;
  }

  return 0;
}
