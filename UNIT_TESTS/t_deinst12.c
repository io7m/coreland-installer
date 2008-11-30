#include <stdio.h>
#include "../install.h"

const char progname[] = "t_deinst12";

int main()
{
  unsigned long i;
  int ret;

  if (!install_init ()) return 112;

  for (i = insthier_len - 1;; --i) {
    ret = deinstall (&insthier[i], 0);
    if (ret != 0) {
      printf("deinstall[%lu] returned %d expected %d\n", i, ret, 0);
      return 1;
    }
    if (i == 0) break;
  }

  return 0;
}
