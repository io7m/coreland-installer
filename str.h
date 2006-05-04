#ifndef STR_H
#define STR_H

unsigned int str_len(const char *);
unsigned int str_copy(const char *, char *);
unsigned int str_ncopy(const char *, char *, unsigned int);

int str_chr(const char *, int);
int str_rchr(const char *, int);

unsigned int str_same(const char *, const char *);
  signed int str_diff(const char *, const char *);

void str_toupper(char *);
void str_tolower(char *);

int str_dup(const char *, char **);
int str_ends(const char *, const char *);
int str_starts(const char *, const char *);

#endif

