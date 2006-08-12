#include "../install.h"

const char progname[] = "t_inst1";

int main()
{
  unsigned long i;

  if (!check_tools()) return 112;

  for (i = insthier_len - 1;; --i) {
    deinstall(&insthier[i], 0);
    if (i == 0) break;
  }

  return 0;
}
