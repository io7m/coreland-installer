#include <stdio.h>
#include <unistd.h>

#define COPY "copy"

char copybuf[8192];
char *from;
char *to;
int uid;
int gid;
unsigned int perm;

void say()
{
  int t_uid;
  int t_gid;
  t_uid = (uid == -1) ? (int) getuid() : uid;
  t_gid = (gid == -1) ? (int) getgid() : gid;
  printf(COPY" %s %s %d:%d %o\n", from, to, t_uid, t_gid, perm);
  fflush(0);
}
int copy()
{
  return 112;
}

int main(int argc, char *argv[])
{
  --argc;
  ++argv;

  if (argc < 5) return 111;

  from = argv[0];
  to = argv[1];
  if (!sscanf(argv[2], "%d", &uid)) return 111;
  if (!sscanf(argv[3], "%d", &gid)) return 111;
  if (!sscanf(argv[4], "%o", &perm)) return 111;

  say();

  if (argc < 6) return copy();
  return 0;
}
