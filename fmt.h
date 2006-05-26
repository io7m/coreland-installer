#ifndef FMT_H
#define FMT_H

#define FMT_ULONGLONG 128 /* (2 ^ 256) digits rounded up to npow2 */
#define FMT_ULONG 40
#define FMT_LEN ((char *) 0)

unsigned int fmt_ulong(char *, unsigned long);
unsigned int fmt_ulongx(char *, unsigned long);
unsigned int fmt_ulongo(char *, unsigned long);

unsigned int fmt_uint(char *, unsigned int);
unsigned int fmt_uintx(char *, unsigned int);
unsigned int fmt_uinto(char *, unsigned int);

unsigned int fmt_ushort(char *, unsigned short);
unsigned int fmt_ushortx(char *, unsigned short);
unsigned int fmt_ushorto(char *, unsigned short);

unsigned int fmt_uchar(char *, unsigned char);
unsigned int fmt_ucharx(char *, unsigned char);
unsigned int fmt_ucharo(char *, unsigned char);

unsigned int fmt_ulonglong(char *, unsigned long long);
unsigned int fmt_ulonglongx(char *, unsigned long long);
unsigned int fmt_ulonglongo(char *, unsigned long long);

unsigned int fmt_float(char *, float *);
unsigned int fmt_double(char *, double *);

unsigned int fmt_str(char *, const char *);
unsigned int fmt_nstr(char *, const char *, unsigned int);

#endif
