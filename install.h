#ifndef INSTALL_H
#define INSTALL_H

#define INSTALL_DRYRUN 0x0001
#define DEINSTALL_DRYRUN 0x0001

#include "sstring.h"

struct install_item {
  const char *from;
  const char *to;
  const char *dir;
  unsigned int perm;
  const char *owner;
  const char *group; 
};

int install(const struct install_item *, unsigned int);
int install_check(const struct install_item *);
int install_libname(sstring *);

int deinstall(const struct install_item *, unsigned int);

extern unsigned int install_failed;
extern const struct install_item insthier[];
extern const unsigned int insthier_size;

#endif
