#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define CHECK "check"
#define str_same(s,t) (strcmp((s),(t)) == 0)

char *file;
char *type;
int uid;
int gid;
unsigned int perm;

int types[] = {
  S_IFREG,
  S_IFCHR,
  S_IFDIR,
  S_IFLNK,
  S_IFSOCK,
  S_IFIFO,
};
char *type_str[] = {
  "file",
  "character_special",
  "directory",
  "symlink",
  "socket",
  "fifo",
};

void die()
{
  printf(CHECK": %s\n", strerror(errno));
  fflush(0);
  _exit(112);
}
void say()
{
  printf(CHECK" %s %d:%d %o %s\n", file, uid, gid, perm, type);
  fflush(0);
}
int check_type(int mode)
{
  unsigned int i;
  int want;
  int got;

  got = 0;
  for (i = 0; i < (sizeof(type_str) / sizeof(char *)); ++i) {
    if (str_same(type_str[i], type)) {
      want = types[i];
      got = 1;
      break;
    }
  }
  if (!got) {
    printf(CHECK": illegal type\n");
    return 0;
  }
  if (mode != want) {
    printf(CHECK": type %s not %s\n", type_str[i], type);
    return 0;
  }
  return 1;
}
int check()
{
  struct stat sb;
  int fd;

  fd = open(file, O_RDONLY);
  if (fd == -1) die();
  if (fstat(fd, &sb) == -1) die();

  if ((sb.st_mode & 07777) != (int) perm) {
    printf(CHECK": mode %o not %o\n", (sb.st_mode & 07777), perm);
    return 1;
  }
  if (uid >= 0) {
    if (sb.st_uid != (unsigned) uid) {
      printf(CHECK": uid %d not %d\n", sb.st_uid, uid);
      return 1;
    }
  }
  if (gid >= 0) {
    if (sb.st_uid != (unsigned) uid) {
      printf(CHECK": gid %d not %d\n", sb.st_gid, gid);
      return 1;
    }
  }
  if (!check_type(sb.st_mode & S_IFMT)) return 1;
  return 0;
}

int main(int argc, char *argv[])
{
  --argc;
  ++argv;

  if (argc < 5) return 111;

  file = argv[0];
  if (!sscanf(argv[1], "%d", &uid)) return 111;
  if (!sscanf(argv[2], "%d", &gid)) return 111;
  if (!sscanf(argv[3], "%o", &perm)) return 111;
  type = argv[4];

  say();

  if (argc < 6) return check();
  return 0;
}
