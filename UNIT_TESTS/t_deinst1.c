#include <stdio.h>
#include "../install.h"

const char progname[] = "t_deinst1";

extern int return_codes[5];

int main()
{
  unsigned long i;
  int ret;

  if (!install_init ()) return 112;

  for (i = insthier_len - 1;; --i) {
    ret = deinstall (&insthier[i], 0);
    if (return_codes[i] != ret) {
      printf("deinstall[%lu] returned %d expected %d\n", i, ret,
              return_codes[i]);
      return 1;
    }
    if (i == 0) break;
  }

  return 0;
}
