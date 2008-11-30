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
int iwin32_file_set_ownership (const char *file, int uid, int gid);
int iwin32_install_init (void);
int iwin32_uidgid_current (int *uid, int *gid);
int iwin32_uidgid_lookup (const char *owner, const char *group, int *uid, int *gid);
#endif

#if INSTALL_OS_TYPE == INSTALL_OS_POSIX
int iposix_file_set_ownership (const char *file, int uid, int gid);
int iposix_install_init (void);
int iposix_uidgid_lookup (const char *, const char *, int *uid, int *gid);
void iposix_uidgid_current (int *, int *);
#endif

#endif
