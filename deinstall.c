#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include "buffer.h"
#include "error.h"
#include "fmt.h"
#include "get_opt.h"
#include "install.h"
#include "open.h"
#include "read.h"
#include "rmkdir.h"
#include "str.h"
#include "sstring.h"
#include "syserr.h"
#include "write.h"

extern const struct install_item insthier[];
extern const unsigned int insthier_size;

static char fbuf1[1024];
static sstring tmpfile = sstring_INIT(fbuf1);

int deinstall(const struct install_item *inst, unsigned int flags)
{
  if (!inst->dir) { syserr_warn1x("error: directory undefined"); return 0; }
  if (inst->to) {
    sstring_trunc(&tmpfile);
    sstring_cats(&tmpfile, inst->dir);
    sstring_cats(&tmpfile, "/");
    sstring_cats(&tmpfile, inst->to);
    sstring_0(&tmpfile);
    if (str_ends(tmpfile.s, ".lib"))
      if (!install_libname(&tmpfile)) return 0;

    buffer_puts(buffer1, "unlink ");
    buffer_puts(buffer1, tmpfile.s);
    buffer_puts(buffer1, "\n");
    if (buffer_flush(buffer1) == -1)
      syserr_warn1sys("error: write: ");

    if (!(flags & DEINSTALL_DRYRUN))
      if (unlink(tmpfile.s) == -1) {
        syserr_warn1sys("error: unlink: "); return 0;
      }
    
    return 1;
  }

  buffer_puts(buffer1, "rmdir ");
  buffer_puts(buffer1, inst->dir);
  buffer_puts(buffer1, "\n");
  if (buffer_flush(buffer1) == -1)
    syserr_warn1sys("error: write: ");

  if (!(flags & DEINSTALL_DRYRUN))
    if (rmdir(inst->dir) == -1) {
      syserr_warn1sys("error: rmdir: "); return 0;
    }

  return 1;
}
