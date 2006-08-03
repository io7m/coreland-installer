#include <grp.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define GID "gid"

char *group;
int gid;

void die()
{
  if (errno)
    printf(GID": %s\n", strerror(errno));
  else
    printf(GID": illegal group\n");
  fflush(0);
  _exit(112);
}
int lookup()
{
  struct group *grp;

  errno = 0;
  grp = getgrnam(group);
  if (!grp) die();

  printf("%u\n", grp->gr_gid);
  return 0;
}
int main(int argc, char *argv[])
{
  --argc;
  ++argv;

  if (argc < 1) return 111;
  group = argv[0];

  return lookup();
}
