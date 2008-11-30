#include <sys/stat.h>
#include <stdio.h>
#include "../install.h"

const char progname[] = "t_instchk1";

extern int return_codes[5];

int main()
{
  unsigned long i;
  unsigned int um;
  int ret;

  um = umask(022);

  if (!install_init ()) return 112;

  for (i = 0; i < insthier_len; ++i) {
    ret = install_check (&insthier[i]);
    if (ret != return_codes[i]) {
      printf("install_check[%lu] returned %d expected %d\n", i, ret,
              return_codes[i]);
      umask (um);
      return 1;
    }
  }

  umask (um);
  return 0;
}
