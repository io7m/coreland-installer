#include "../install.h"

const struct install_item insthier[] = {
  {"files/file.lib", "file.lib", "home", 0600, "nobody", "nobody"},
};

const unsigned int insthier_size = sizeof(insthier) / sizeof(struct install_item);
