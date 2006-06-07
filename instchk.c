#include "buffer.h"
#include "fmt.h"
#include "install.h"
#include "syserr.h"

const char progname[] = "instchk";

int main()
{
  char cnum[FMT_ULONG];
  unsigned int ind;

  for (ind = 0; ind < insthier_size; ++ind)
    install_check(&insthier[ind]);    

  if (install_failed) {
    cnum[fmt_uint(cnum, install_failed)] = 0;
    buffer_puts(buffer1, cnum);
    buffer_puts(buffer1, " of ");
    cnum[fmt_uint(cnum, insthier_size)] = 0;
    buffer_puts(buffer1, cnum);
    buffer_puts(buffer1, " files failed to install\n");
  }

  if (buffer_flush(buffer1) == -1) syserr_die1sys(112, "fatal: write: ");
  return 0;
}
