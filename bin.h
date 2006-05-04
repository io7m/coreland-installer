#ifndef BIN_H
#define BIN_H

int bin_chr(const char *, unsigned int, int);
int bin_rchr(const char *, unsigned int, int);

void bin_tolower(char *, unsigned int);
void bin_toupper(char *, unsigned int);

void bin_copy(const char *, char *, unsigned int);
void bin_copyr(char *, const char *, unsigned int);
void bin_zero(char *, unsigned int);
void bin_set(char *, unsigned int, int);

int bin_diff(const char *, const char *, unsigned int);
int bin_same(const char *, const char *, unsigned int);
unsigned int bin_count(const char *, unsigned int, int);

#endif
