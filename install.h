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

struct install_status_t {
  enum {
    INSTALL_STATUS_OK,
    INSTALL_STATUS_ERROR,
    INSTALL_STATUS_FATAL
  } status;
  const char *message;
};

#define INSTALL_STATUS_INIT {INSTALL_STATUS_FATAL,0}

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

typedef struct {
  unsigned int value;
} permissions_t;

struct install_status_t install_init (void);
struct install_status_t install (struct install_item *, unsigned int);
struct install_status_t install_check (struct install_item *);
struct install_status_t deinstall (struct install_item *, unsigned int);

#include <errno.h>

const char *install_error (int);
extern struct install_item insthier[];
extern unsigned long insthier_len;
extern unsigned long install_failed;
extern char exec_suffix [16];
extern char dlib_suffix [16];

#include "install_os.h"

int install_compare_gid (group_id_t, group_id_t);
int install_compare_uid (user_id_t, user_id_t);
int install_compare_permissions (permissions_t, permissions_t);
int install_file_get_mode (const char *, permissions_t *);
int install_file_get_ownership (const char *, user_id_t *, group_id_t *);
int install_file_link (const char *, const char *);
int install_file_set_ownership (const char *, user_id_t, group_id_t);
int install_file_size (const char *, unsigned long *);
int install_file_type (const char *, enum install_file_type_t *, int);
int install_file_type_lookup (const char *, enum install_file_type_t *);
int install_file_type_name_lookup (enum install_file_type_t, const char **);
int install_gid_current (group_id_t *);
int install_gid_lookup (const char *, group_id_t *);
int install_mkdir (const char *, unsigned int);
int install_uid_current (user_id_t *);
int install_uid_lookup (const char *, user_id_t *);
struct install_status_t install_file_copy (const char *, const char *, user_id_t, group_id_t, permissions_t);
unsigned int install_fmt_gid (char *, group_id_t);
unsigned int install_fmt_uid (char *, user_id_t);
unsigned int install_scan_gid (const char *, group_id_t *);
unsigned int install_scan_uid (const char *, user_id_t *);
unsigned int install_umask (unsigned int);
void install_gid_free (group_id_t *);
void install_uid_free (user_id_t *);

#endif
