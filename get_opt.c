#include "buffer.h"
#include "get_opt.h"

char *optprogname = 0;
char *optarg = 0;
int opterr = 1;
int optproblem = 0;
int optind = 1;
int optpos = 0;
int optdone = -1;
int opteof = -1;

static int subgetopt(int argc, char **argv, char *opts)
{
  int c;
  char *s;

  optarg = 0;
  if (!argv || (optind >= argc) || !argv[optind]) return optdone;
  if (optpos && !argv[optind][optpos]) {
    ++optind;
    optpos = 0;
    if ((optind >= argc) || !argv[optind]) return optdone;
  }
  if (!optpos) {
    if (argv[optind][0] != '-') return optdone;
    ++optpos;
    c = argv[optind][1];
    if ((c == '-') || (c == 0)) {
      if (c) ++optind;
      optpos = 0;
      return optdone;
    }
  }
  c = argv[optind][optpos]; ++optpos;
  s = opts;

  while (*s) {
    if (c == *s) {
      if (s[1] == ':') {
        optarg = argv[optind] + optpos;
        ++optind;
        optpos = 0;
        if (!*optarg) {
          optarg = argv[optind];
          if ((optind >= argc) || !optarg) {
            optproblem = c;
            return '?';
          }
          ++optind;
        }
      }
      return c;
    }
    ++s;
    if (*s == ':') ++s;
  }
  optproblem = c;
  return '?';
}

int get_opt(int argc, char **argv, char *opts)
{
  int c;
  char *s;

  if (!optprogname) {
    optprogname = *argv;
    if (!optprogname) optprogname = "";
    for (s = optprogname; *s; ++s)
      if (*s == '/') optprogname = s + 1;
  }

  c = subgetopt(argc, argv, opts);

  if (opterr)
    if (c == '?') {
      char chp[2];
      chp[0] = optproblem;
      chp[1] = '\n';

      buffer_puts(buffer2, optprogname);
      if (argv[optind] && optind < argc)
        buffer_puts(buffer2, ": illegal option -- ");
      else
        buffer_puts(buffer2, ": option requires an argument -- ");
      buffer_put(buffer2, chp, 2);
      buffer_flush(buffer2);
    }

  return c;
}
