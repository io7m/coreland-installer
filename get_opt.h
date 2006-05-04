#ifndef GETOPT_H
#define GETOPT_H

extern int opteof;
extern int optproblem;
extern int optind;
extern int optpos;
extern int optdone;
extern char *optprogname;
extern char *optarg;

int get_opt(int, char **, char *);

#endif
