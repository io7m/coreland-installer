#include "../install.h"

#define TODIR "installto/t2"

struct install_item insthier[] = {
  {INST_MKDIR,   0,                 0,       TODIR, 0, 0, 0700},
  {INST_COPY,    "files/t2/t2.vlb", 0,       TODIR, 0, 0, 0600},
  {INST_LIBLINK, "files/t2/t2.vlb", "libt2", TODIR, 0, 0, 0600},
};
unsigned long insthier_len = sizeof(insthier) / sizeof(struct install_item);
