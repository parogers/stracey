#include <stdio.h>
#include <string.h>

int main(void)
{
  char *s = "hello world\n";

  write(1, s, strlen(s));

  return 0;
}
