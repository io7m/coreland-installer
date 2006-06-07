#include "../install.h"

const struct install_item insthier[] = {
  {0, 0, "/usr/lib", 0755, "root", "wheel"},
  {"files/file.lib", 0, "/usr/lib", 0444, "root", "wheel"},
  {"files/libxyz.a", 0, "/usr/lib", 0444, "root", "wheel"},
  {"nonexistant", 0, "/usr/lib", 0444, "root", "wheel"},
  {0, 0, 0, 0, 0, 0},
  {0, "to", "/usr/lib", 0444, 0, 0},
  {"file", "file2", "dir", 0444, "1234XNOBODYx123", "1234XNOBODYx123"},
};

const unsigned int insthier_size = sizeof(insthier) / sizeof(struct install_item);
