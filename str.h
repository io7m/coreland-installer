#ifndef STR_H
#define STR_H

unsigned long str_len(const char *);

int str_chr(const char *, int);
int str_rchr(const char *, int);

int str_diff(const char *, const char *);
int str_ndiff(const char *, const char *, unsigned long);

void str_toupper(char *);
void str_tolower(char *);

int str_dup(const char *, char **);
int str_ends(const char *, const char *);
int str_starts(const char *, const char *);

#define str_same(s,t) (str_diff((s),(t)) == 0)
#define str_nsame(s,t,n) (str_ndiff((s),(t),(n)) == 0)

#endif
