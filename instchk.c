#include "buffer.h"
#include "fmt.h"
#include "install.h"
#include "syserr.h"

const char progname[] = "instchk";

int main()
{
  char cnum[FMT_ULONG];
  char cnum2[FMT_ULONG];
  unsigned int ind;

  for (ind = 0; ind < insthier_size; ++ind)
    install_check(&insthier[ind]);    

  if (install_failed) {
    if (install_failed == insthier_size) {
      buffer_puts(buffer1, "None of the files were correctly installed!\n");
    } else {
      cnum[fmt_uint(cnum, install_failed)] = 0;
      cnum2[fmt_uint(cnum2, insthier_size)] = 0;
      buffer_puts(buffer1, cnum);
      buffer_puts(buffer1, " out of ");
      buffer_puts(buffer1, cnum2);
      buffer_puts(buffer1, " files were incorrectly installed.\n");
    }
  } else {
    buffer_puts(buffer1, "All files were correctly installed.\n");
  }

  if (buffer_flush(buffer1) == -1) syserr_die1sys(112, "fatal: write: ");
  return 0;
}
