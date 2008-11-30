#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include "../install.h"

const char progname[] = "t_inst2";

int main()
{
  unsigned long i;
  unsigned int um;
  int r;
  int tret;

  um = umask (022);
  tret = 0;

  if (!install_init ()) return 112;

  printf("installing...\n");
  for (i = 0; i < insthier_len; ++i) {
    r = install (&insthier[i], 0);
    if (r == 0) {
      printf ("install %lu failed\n", i);
      tret = 1;
    }
  }

  fflush (0);
  umask (um);
  return tret;
}
