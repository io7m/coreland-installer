#include "install.h"

const struct install_item insthier[] = {
  {0, 0, "/usr/local/share/coreland/lib", 0755, "root", "wheel"},
  {0, "error.a", "/usr/local/share/coreland/lib", 0444, "root", "wheel"},
};

/*
const struct install_item insthier[] = {
  {0, 0, 0, 0, 0, 0},
};
*/

const unsigned int insthier_size = sizeof(insthier) / sizeof(struct install_item);
