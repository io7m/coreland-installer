#ifndef BUFFER_H
#define BUFFER_H

#define BUFFER_OUTSIZE 8192
#define BUFFER_INSIZE 8192

typedef struct {
  char *buf;
  unsigned long pos;
  unsigned long size;
  int fd;
  int (*op)(int, char *, unsigned long);
} buffer;

#define buffer_INIT(op,fd,buf,len) { (buf), 0, (len), (fd), (op) }

void buffer_init(buffer *, int (*)(), int, char *, unsigned long);

int buffer_get(buffer *, char *, unsigned long);
int buffer_feed(buffer *);
char *buffer_peek(buffer *);
void  buffer_seek(buffer *, unsigned long);

int buffer_flush(buffer *);
int buffer_put(buffer *, const char *, unsigned long);
int buffer_puts(buffer *, const char *);
int buffer_putflush(buffer *, const char *, unsigned long);
int buffer_putsflush(buffer *, const char *);

int buffer_copy(buffer *, buffer *);

#define buffer_PEEK(s) ( (s)->buf + (s)->size )
#define buffer_SEEK(s,len) ( ( (s)->pos -= (len) ) , ( (s)->size += (len) ) )
#define buffer_GETC(s,c) \
  ( ((s)->pos > 0) \
    ? ( *(c) = (s)->buf[(s)->size], buffer_SEEK((s),1), 1 ) \
    : buffer_get((s),(c),1) \
  )

extern buffer *buffer0;
extern buffer *buffer1;
extern buffer *buffer2;

#endif
