#include "ctxt.h"
#include "install.h"

struct install_item insthier[] = {
  {INST_MKDIR, 0, 0, ctxt_repos, 0, 0, 0755},
  {INST_COPY, "inst-check.c", 0, ctxt_repos, 0, 0, 0444},
  {INST_COPY, "inst-copy.c", 0, ctxt_repos, 0, 0, 0444},
  {INST_COPY, "inst-dir.c", 0, ctxt_repos, 0, 0, 0444},
  {INST_COPY, "install.c", 0, ctxt_repos, 0, 0, 0444},
  {INST_COPY, "installer.c", 0, ctxt_repos, 0, 0, 0444},
  {INST_LIBLINK, "file.lib", "libfile", ctxt_repos, 0, 0, 0},
  {INST_LIBLINK, "file.lib", "libfile", ctxt_repos, 0, 0, 0},
};
unsigned long insthier_len = sizeof(insthier) / sizeof(struct install_item);
