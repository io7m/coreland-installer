#ifndef INSTALL_OS_H
#define INSTALL_OS_H

#define INSTALL_OS_POSIX 0x0000
#define INSTALL_OS_WIN32 0x0001

/* win32 */
#ifndef INSTALL_OS_TYPE
#  if defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(__WIN64__) || defined(__TOS_WIN__)
#    define INSTALL_OS_TYPE INSTALL_OS_WIN32
#  endif
#endif

/* fallback OS type - posix */
#ifndef INSTALL_OS_TYPE
#  define INSTALL_OS_TYPE INSTALL_OS_POSIX
#endif

/*
 * prototypes
 */

#if INSTALL_OS_TYPE == INSTALL_OS_WIN32
typedef struct { PSID value; } user_id_t;
typedef struct { PSID value; } group_id_t;

#define INSTALL_NULL_UID {NULL}
#define INSTALL_NULL_GID {NULL}

int iwin32_file_set_ownership (const char *file, user_id_t uid, group_id_t gid);
int iwin32_install_init (void);
int iwin32_uidgid_current (user_id_t *uid, group_id_t *gid);
int iwin32_uidgid_lookup (const char *owner, user_id_t *uid, const char *group, group_id_t *gid);
#endif

#if INSTALL_OS_TYPE == INSTALL_OS_POSIX
typedef struct { int value; } user_id_t;
typedef struct { int value; } group_id_t;

#define INSTALL_NULL_UID {-1}
#define INSTALL_NULL_GID {-1}

int iposix_file_set_ownership (const char *file, user_id_t uid, group_id_t gid);
int iposix_install_init (void);
int iposix_uidgid_lookup (const char *, user_id_t *uid, const char *, group_id_t *gid);
void iposix_uidgid_current (user_id_t *, group_id_t *);
#endif

#endif
