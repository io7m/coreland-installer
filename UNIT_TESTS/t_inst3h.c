#include "../install.h"

#define TODIR "installto/t3"

struct install_item insthier[] = {
  {INST_MKDIR,     0,                      0,           TODIR, 0, 0, 0700},
  {INST_COPY,      "files/t3/file.c",      0,           TODIR, 0, 0, 0600},
  {INST_COPY_EXEC, "files/t3/executable",  0,           TODIR, 0, 0, 0700},
  {INST_COPY,      "files/t3/nonexistent", 0,           TODIR, 0, 0, 0600},
  {INST_COPY,      "files/t3/file.c",      "renamed.c", TODIR, 0, 0, 0600},
  {INST_SYMLINK,   "file.c",               "symlink",   TODIR, 0, 0, 0600},
};
unsigned long insthier_len = sizeof(insthier) / sizeof(struct install_item);

int return_codes[6] = {
  INSTALL_STATUS_OK,
  INSTALL_STATUS_OK,
  INSTALL_STATUS_OK,
  INSTALL_STATUS_ERROR,
  INSTALL_STATUS_OK,
  INSTALL_STATUS_OK,
};
