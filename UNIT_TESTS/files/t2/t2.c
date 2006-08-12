#include <stdio.h>

void func()
{
  int x;
  x = 8;
  x <<= 8;
  x <<= 8;
  printf("%d\n", x);
}
