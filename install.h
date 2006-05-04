#ifndef INSTALL_H
#define INSTALL_H

#define INSTALL_DRYRUN 0x0001

struct install_item {
  const char *file;
  const char *home;
  unsigned int perm;
  const char *owner;
  const char *group; 
};

int install(const struct install_item *, unsigned int);
int install_check(const struct install_item *);

#endif
