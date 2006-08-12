#include <sys/stat.h>
#include <stdio.h>
#include "../install.h"

const char progname[] = "t_inst1";

extern int return_codes[5];

int main()
{
  unsigned long i;
  unsigned int um;
  int ret;

  um = umask(022);

  if (!check_tools()) return 112;

  for (i = 0; i < insthier_len; ++i) {
    ret = install(&insthier[i], 0);
    if (return_codes[i] != ret) {
      printf("install[%lu] returned %d expected %d\n", i, ret, return_codes[i]);
      umask(um);
      return 1;
    }
  }

  umask(um);
  return 0;
}
