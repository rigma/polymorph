#include <stdlib.h>
#include <stdio.h>

#include <type/polynomial.h>
#include <arithmetic.h>

void test();

int main(int argc, char **argv)
{
	test();

	system("pause");

	return EXIT_SUCCESS;
}

void test()
{
	polynomial_t *p = NULL, *q = NULL, *r = NULL;

	p = polynomial_init("P");
	q = polynomial_init("Q");

	polynomial_append(p, complex_init(3.0, 0.0), 2);
	polynomial_append(p, complex_init(2.0, 0.0), 1);
	polynomial_append(p, complex_init(1.0, 0.0), 0);

	polynomial_append(q, complex_init(9.0, 0.0), 2);
	polynomial_append(q, complex_init(4.0, 0.0), 1);
	polynomial_append(q, complex_init(1.0, 0.0), 0);

	polynomial_display(p);
	polynomial_display(q);

	r = polynomial_prod(p, q, NULL);
	polynomial_display(r);

	polynomial_free(p);
	polynomial_free(q);
	polynomial_free(r);
}
