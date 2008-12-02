#include <stdio.h>
#include "../install.h"

const char progname[] = "t_deinst1";

extern unsigned int return_codes[5];

int main()
{
  unsigned long i;
  struct install_status_t status;

  if (!install_init ()) return 112;

  for (i = insthier_len - 1;; --i) {
    status = deinstall (&insthier[i], 0);
    if (return_codes[i] != status.status) {
      printf("deinstall[%lu] returned %d expected %d\n", i, status.status,
              return_codes[i]);
      return 1;
    }
    if (i == 0) break;
  }

  return 0;
}
