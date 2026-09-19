#include <stdio.h>
#include <stdlib.h>

struct inner {
  char c;
  long ok;
};

struct flex_array {
  int nr;
  int unused;
  union {
    long x;
    struct inner union_elem[];
  };
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
  a->union_elem[0].ok = 0;
  for (int k = 0; k < n; k++)
    a->union_elem[k].c = 'c';

  for (int i = 0; i < l; i++) {
    for (int j = 0; j < n; j++)
      if (a->nr > 0 && a->union_elem[j].c == 'c') {
	a->union_elem[j].ok = 0;
	if (j != 1)
	  a->union_elem[1].ok++;
      }
  }
  free((void*)a);
  return 0;
}
