#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define LINK "link"

char *dir;
char *src;
char *dst;

void say()
{
  printf(LINK" %s %s %s\n", dir, src, dst);
  fflush(0);
}
void complain(const char *s)
{
  if (s)
    printf(LINK": %s: %s\n", s, strerror(errno));
  else
    printf(LINK": %s\n", strerror(errno));
}
int create_link()
{
  int dirfd;

  dirfd = open(dir, O_RDONLY);
  if (dirfd == -1) { complain("open"); return 112; }
  if (fchdir(dirfd) == -1) { complain("fchdir"); return 113; }
  if (symlink(src, dst) == -1) { complain("symlink"); return 114; }
  return 0;
}
int main(int argc, char *argv[])
{
  --argc;
  ++argv;

  if (argc < 3) return 111;

  dir = argv[0];
  src = argv[1];
  dst = argv[2];

  say();

  if (argc < 4) return create_link();
  return 0;
}
