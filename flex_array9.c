#include <stdio.h>
#include <stdlib.h>

struct inner {
	int unused;
	int ok;
};

struct flex_array {
	int len;
	struct inner index[];
};

int main(int argc, char *argv[])
{
	int i, j;
	int n = 8, l = 1000000;
	volatile struct flex_array *a;

	if (argc > 1)
		l = atoi(argv[1]);
	if (argc > 2)
		n = atoi(argv[2]);

	a = calloc(1, sizeof(*a) + n * sizeof(*a->index));
	if (a == NULL)
		return 1;
	a->len = n;

	for (i = 0; i < l; i++) {
		for (j = 0; j < a->len; j++)
			a->index[j].ok++;
	}
	free((void *)a);
	return 0;

}

