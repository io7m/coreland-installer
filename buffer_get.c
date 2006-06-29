#include "bin.h"
#include "buffer.h"
#include "error.h"

static long single_read(long (*op)(int, char *, unsigned long),
                        int fd, char *buf, unsigned long len)
{
  long r;

  for (;;) {
    r = op(fd, buf, len);
    if (r == -1)
      if (errno == error_intr) continue;
    return r;
  }
}

static long get_this(buffer *b, char *s, unsigned long len)
{
  if (len > b->pos) len = b->pos;
  b->pos -= len;
  bin_copy(b->buf + b->size, s, len);
  b->size += len;
  return len; 
}

long buffer_feed(buffer *b)
{
  long r;
 
  if (b->pos) return b->pos;
  r = single_read(b->op, b->fd, b->buf, b->size);
  if (r <= 0) return r;
  b->pos = r;
  b->size -= r;
  if (b->size > 0) bin_copyr(b->buf + b->size, b->buf, r);
  return r;
}

long buffer_get(buffer *b, char *s, unsigned long len)
{
  long r;
 
  if (b->pos > 0) return get_this(b, s, len);
  if (b->size <= len) return single_read(b->op, b->fd, s, len);
  r = buffer_feed(b);
  if (r <= 0) return r;
  return get_this(b, s, len);
}

char *buffer_peek(buffer *b)
{
  return b->buf + b->size;
}

void buffer_seek(buffer *b, unsigned long len)
{
  b->size += len;
  b->pos -= len;
}
