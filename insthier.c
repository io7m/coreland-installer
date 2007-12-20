/* $Rev$ */

#include "ctxt.h"
#include "install.h"

struct install_item insthier[] = {
  {INST_MKDIR, 0, 0, ctxt_repos, 0, 0, 0755},
  {INST_COPY, "deinstaller.c", 0, ctxt_repos, 0, 0, 0444},
  {INST_COPY, "inst-check.c", 0, ctxt_repos, 0, 0, 0444},
  {INST_COPY, "inst-copy.c", 0, ctxt_repos, 0, 0, 0444},
  {INST_COPY, "inst-dir.c", 0, ctxt_repos, 0, 0, 0444},
  {INST_COPY, "inst-link.c", 0, ctxt_repos, 0, 0, 0444},
  {INST_COPY, "install_error.c", 0, ctxt_repos, 0, 0, 0444},
  {INST_COPY, "installer.c", 0, ctxt_repos, 0, 0, 0444},
  {INST_COPY, "instchk.c", 0, ctxt_repos, 0, 0, 0444},
  {INST_COPY, "install.h", 0, ctxt_repos, 0, 0, 0444},
  {INST_COPY, "installer.ld", 0, ctxt_repos, 0, 0, 0444},
  {INST_COPY, "deinstaller.ld", 0, ctxt_repos, 0, 0, 0444},
  {INST_COPY, "instchk.ld", 0, ctxt_repos, 0, 0, 0444},
  {INST_COPY, "inst-check.ld", 0, ctxt_repos, 0, 0, 0444},
  {INST_COPY, "inst-copy.ld", 0, ctxt_repos, 0, 0, 0444},
  {INST_COPY, "inst-dir.ld", 0, ctxt_repos, 0, 0, 0444},
  {INST_COPY, "inst-link.ld", 0, ctxt_repos, 0, 0, 0444},
  {INST_COPY, "postinstall", 0, ctxt_repos, 0, 0, 0555},
  {INST_COPY, "Mkf-deinstall", 0, ctxt_repos, 0, 0, 0444},
  {INST_COPY, "Mkf-install", 0, ctxt_repos, 0, 0, 0444},
  {INST_COPY, "Mkf-instchk", 0, ctxt_repos, 0, 0, 0444},
};
unsigned long insthier_len = sizeof(insthier) / sizeof(struct install_item);
