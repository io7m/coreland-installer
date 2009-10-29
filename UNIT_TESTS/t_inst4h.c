#include "../install.h"

#define TODIR "installto/t4"

struct install_item insthier[] = {
  {INST_MKDIR,   0,                 0,       TODIR, 0, 0, 0700},
  {INST_COPY,    "files/t4/t4.vlb", 0,       TODIR, 0, 0, 0600},
  {INST_LIBLINK, "files/t4/t4.vlb", "libt4", TODIR, 0, 0, 0600},
};
unsigned long insthier_len = sizeof(insthier) / sizeof(struct install_item);
