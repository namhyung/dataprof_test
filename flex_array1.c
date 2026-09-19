#include <stdio.h>
#include <stdlib.h>

struct inner {
  char c;
  long ok;
};

struct flex_array {
  int nr;
  int unused;
  struct inner flex[];
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
  a->flex[0].ok = 0;
  for (int k = 0; k < n; k++)
    a->flex[k].c = 'c';

  for (int i = 0; i < l; i++) {
    for (int j = 0; j < n; j++)
      if (a->nr > 0 && a->flex[j].c == 'c') {
	a->flex[j].ok = 0;
	if (j != 1)
	  a->flex[1].ok++;
      }
  }
  free((void*)a);
  return 0;
}
