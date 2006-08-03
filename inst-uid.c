#include <pwd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define UID "uidgid"

char *user;
int uid;

void die()
{
  if (errno)
    printf(UID": %s\n", strerror(errno));
  else
    printf(UID": illegal user\n");
  fflush(0);
  _exit(112);
}
int lookup()
{
  struct passwd *pwd;

  errno = 0;
  pwd = getpwnam(user);
  if (!pwd) die();

  printf("%u\n", pwd->pw_uid);
  return 0;
}
int main(int argc, char *argv[])
{
  --argc;
  ++argv;

  if (argc < 1) return 111;
  user = argv[0];

  return lookup();
}
