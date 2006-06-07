#include "install.h"

const struct install_item insthier[] = {
  {"insthier.o", 0, "/usr/local/lib/coreland", 0444, "root", "wheel"},
};

const unsigned int insthier_size = sizeof(insthier) / sizeof(struct install_item);
