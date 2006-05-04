#ifndef FMT_H
#define FMT_H

#define FMT_UINT32 11
#define FMT_UINT32O 14 + 2
#define FMT_UINT32X (FMT_UINT32 + 2)
#define FMT_UINT32ANY 16

#define FMT_UINT64 21
#define FMT_UINT64O 24 + 2
#define FMT_UINT64X (FMT_UINT64 + 2)
#define FMT_UINT64ANY 32

#define FMT_BYTE 4
#define FMT_BYTEO 4 + 2
#define FMT_BYTEX (FMT_BYTE + 2)
#define FMT_BYTEANY 8

#include "uint32.h"

unsigned int fmt_u32(char *, uint32);
unsigned int fmt_u32o(char *, uint32);
unsigned int fmt_u32x(char *, uint32);

#include "uint64.h"

unsigned int fmt_u64(char *, uint64);
unsigned int fmt_u64o(char *, uint64);
unsigned int fmt_u64x(char *, uint64);

unsigned int fmt_byte(char *, unsigned char);
unsigned int fmt_byteo(char *, unsigned char);
unsigned int fmt_bytex(char *, unsigned char);

#endif
