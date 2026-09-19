#include <stdio.h>
#include <stdlib.h>

struct inner {
  char c;
  long ok;
};

struct flex_array {
  int nr;
  int unused;
  struct inner is_typedef[];
};

typedef struct flex_array flex_array_t;

int main(int argc, char *argv[])
{
  register int l = 1000000;
  register int n = 8;
  volatile flex_array_t *a;

  if (argc > 1)
    l = atoi(argv[1]);
  if (argc > 2)
    n = atoi(argv[2]);

  a = malloc(sizeof(*a) + n * sizeof(struct inner));
  if (a == NULL)
    return 1;

  a->nr = n;
  a->is_typedef[0].ok = 0;
  for (int k = 0; k < n; k++)
    a->is_typedef[k].c = 'c';

  for (int i = 0; i < l; i++) {
    for (int j = 0; j < n; j++)
      if (a->nr > 0 && a->is_typedef[j].c == 'c') {
	a->is_typedef[j].ok = 0;
	if (j != 1)
	  a->is_typedef[1].ok++;
      }
  }
  free((void*)a);
  return 0;
}
