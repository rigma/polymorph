#include <stdlib.h>
#include <stdio.h>

#include <type/monomial.h>

int main(int argc, char **argv)
{
	monomial_t *m = monomial_init(complex_init(1.0, 0.0), 2);
	complex_t *z = monomial_eval(m, 2.0);

	printf("Hello world !\n");
	printf("2 ^ 2 = %lf\n", z->re);

	monomial_free(m);
	complex_free(z);

	return EXIT_SUCCESS;
}
