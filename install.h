#ifndef INSTALL_H
#define INSTALL_H

#define INSTALL_DRYRUN 0x0001

#define MAX_PATHLEN 1024

#define IOP_COPY 0
#define IOP_LINK 1
#define IOP_MKDIR 2
#define IOP_LIBLINK 3

struct install_item {
  unsigned int op;
  const char *from;
  const char *to;
  const char *dir;
  unsigned int perm;
  const char *owner;
  const char *group; 
};

int install(struct install_item *, unsigned int);
int install_check(struct install_item *);
int deinstall(struct install_item *, unsigned int);

extern unsigned int install_failed;
extern unsigned int deinstall_failed;
extern struct install_item insthier[];
extern unsigned int insthier_size;

#endif
