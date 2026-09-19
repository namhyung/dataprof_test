#include <stdio.h>
#include <stdlib.h>

struct inner {
  char c;
  long ok;
};

struct outer {
  int x;
  //int y;
  struct inner inner[];
};

struct flex_array2 {
  int nr;
  int unused;
  struct outer outer;
};

int main(int argc, char *argv[])
{
  register int l = 1000000;
  register int n = 8;
  volatile struct flex_array2 *a;

  if (argc > 1)
    l = atoi(argv[1]);
  if (argc > 2)
    n = atoi(argv[2]);

  a = malloc(sizeof(*a) + n * sizeof(struct inner));
  if (a == NULL)
    return 1;

  a->nr = n;
  a->outer.inner[0].ok = 0;
  for (int k = 0; k < n; k++)
    a->outer.inner[k].c = 'c';

  for (int i = 0; i < l; i++) {
    for (int j = 0; j < n; j++)
      if (a->nr > 0 && a->outer.inner[j].c == 'c') {
	a->outer.inner[j].ok = 0;
	if (j != 1)
	  a->outer.inner[1].ok++;
      }
  }
  free((void*)a);
  return 0;
}
