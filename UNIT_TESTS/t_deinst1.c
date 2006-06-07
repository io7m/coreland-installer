#include "../buffer.h"
#include "../install.h"
#include "../syserr.h"

int main()
{
  unsigned int ind;

  for (ind = 0; ind < insthier_size; ++ind)
    deinstall(&insthier[ind], INSTALL_DRYRUN);    

  if (buffer_flush(buffer1) == -1) syserr_die1sys(112, "fatal: write: ");
  return 0;
}
