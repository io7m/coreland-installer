#ifndef SSTRING_H
#define SSTRING_H

typedef struct sstring {
  char* s;
  unsigned int len; /* length of contents */
  unsigned int a;   /* allocated */
} sstring;

#define sstring_INIT(s) { (s), (0), (sizeof s) }

void sstring_init(sstring *, char *, unsigned int);

unsigned int sstring_catb(sstring *, const char *, unsigned int);
unsigned int sstring_cats(sstring *, const char *);
unsigned int sstring_cat(const sstring *, sstring *);

unsigned int sstring_cpyb(sstring *, const char *, unsigned int);
unsigned int sstring_cpys(sstring *, const char *);
unsigned int sstring_copy(const sstring *, sstring *);

unsigned int sstring_0(sstring *);

unsigned int sstring_chop(sstring *, unsigned int);
void sstring_trunc(sstring *);

#endif
