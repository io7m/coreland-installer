#ifndef INSTALL_H
#define INSTALL_H

#define INSTALL_DRYRUN 0x0001

#define INST_COPY 0
#define INST_SYMLINK 1
#define INST_MKDIR 2
#define INST_LIBLINK 3
#define INST_COPY_EXEC 4

#define INSTALL_MAX_PATHLEN 1024
#define INSTALL_MAX_MSGLEN  8192

#define INSTALL_NULL_USER_NAME ":"
#define INSTALL_NULL_GROUP_NAME ":"

enum install_file_type_t {
  INSTALL_FILE_TYPE_FILE,
  INSTALL_FILE_TYPE_CHARACTER_SPECIAL,
  INSTALL_FILE_TYPE_DIRECTORY,
  INSTALL_FILE_TYPE_SYMLINK,
  INSTALL_FILE_TYPE_SOCKET,
  INSTALL_FILE_TYPE_FIFO
};

struct install_item {
  int op;
  char *src;
  char *dst;
  char *dir;
  char *owner;
  char *group;
  int perm;
};

int install_init (void);
int install (struct install_item *, unsigned int);
int install_check (struct install_item *);
int deinstall (struct install_item *, unsigned int);

const char *install_error (int);

extern struct install_item insthier[];
extern unsigned long insthier_len;
extern unsigned long install_failed;

#include "install_os.h"

int install_compare_gid (group_id_t, group_id_t);
int install_compare_uid (user_id_t, user_id_t);
int install_file_get_mode (const char *, unsigned int *);
int install_file_get_ownership (const char *, user_id_t *, group_id_t *);
int install_file_set_ownership (const char *, user_id_t, group_id_t);
int install_file_type (const char *, enum install_file_type_t *, int);
int install_file_type_lookup (const char *, enum install_file_type_t *);
int install_file_type_name_lookup (enum install_file_type_t, const char **);
int install_file_copy (const char *, const char *, user_id_t, group_id_t, unsigned int);
int install_file_size (const char *, unsigned long *);
int install_gid_current (group_id_t *);
int install_gid_lookup (const char *, group_id_t *);
int install_uid_current (user_id_t *);
int install_uid_lookup (const char *, user_id_t *);
unsigned int install_fmt_gid (char *, group_id_t);
unsigned int install_fmt_uid (char *, user_id_t);
unsigned int install_scan_gid (const char *, group_id_t *);
unsigned int install_scan_uid (const char *, user_id_t *);

#endif
