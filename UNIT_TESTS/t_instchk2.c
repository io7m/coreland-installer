#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include "../install.h"

const char progname[] = "t_instchk2";

int main()
{
  unsigned long i;
  unsigned int um;
  int r;
  int tret;

  um = install_umask (022);
  tret = 0;

  if (!install_init ()) return 112;

  printf("checking...\n");
  for (i = 0; i < insthier_len; ++i) {
    r = install_check (&insthier[i]);
    if (r == 0) tret = 1;
  }

  fflush (0);
  install_umask (um);
  return tret;
}
