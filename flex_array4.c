#include <stdio.h>
#include <stdlib.h>

struct inner {
  char c;
  short ok;
};

struct flex_array {
  int nr;
  long unused;
  int unused2;
  struct inner unaligned[];
};

int main(int argc, char *argv[])
{
  register int l = 1000000;
  register int n = 8;
  volatile struct flex_array *a;

  if (argc > 1)
    l = atoi(argv[1]);
  if (argc > 2)
    n = atoi(argv[2]);

  a = malloc(sizeof(*a) + n * sizeof(struct inner));
  if (a == NULL)
    return 1;

  a->nr = n;
  a->unaligned[0].ok = 0;
  for (int k = 0; k < n; k++)
    a->unaligned[k].c = 'c';

  for (int i = 0; i < l; i++) {
    for (int j = 0; j < n; j++)
      if (a->nr > 0 && a->unaligned[j].c == 'c') {
	a->unaligned[j].ok = 0;
	if (j != 1)
	  a->unaligned[1].ok++;
      }
  }
  free((void*)a);
  return 0;
}
