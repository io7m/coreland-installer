#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include "../install.h"

const char progname[] = "t_deinst2";

int main()
{
  unsigned long i;
  unsigned int um;
  int r;
  int tret;

  um = umask(022);
  tret = 0;

  if (!check_tools()) return 112;

  printf("deinstalling...\n");
  for (i = insthier_len - 1;; --i) {
    r = deinstall(&insthier[i], 0);
    if (r == 0) tret = 1;
    if (i == 0) break;
  }

  fflush(0);
  umask(um);
  return tret;
}