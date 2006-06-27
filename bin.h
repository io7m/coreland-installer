#ifndef BIN_H
#define BIN_H

int bin_chr(const char *, unsigned long, int);
int bin_rchr(const char *, unsigned long, int);

void bin_tolower(char *, unsigned long);
void bin_toupper(char *, unsigned long);

void bin_copy(const char *, char *, unsigned long);
void bin_copyr(char *, const char *, unsigned long);
void bin_zero(char *, unsigned long);
void bin_set(char *, unsigned long, int);

int bin_diff(const char *, const char *, unsigned long);
int bin_same(const char *, const char *, unsigned long);
unsigned long bin_count(const char *, unsigned long, int);

#endif
