#include <stdlib.h>
#include <stdio.h>

#include <type/polymorph.h>
#include <type/polynomial.h>
#include <arithmetic.h>
#include <analysis.h>

#include <io/console.h>

void test();

int main(int argc, char **argv)
{
	/*console_t *console = console_init();

	return console_run(console);*/

	test();

	system("pause");

	return EXIT_SUCCESS;
}

void test()
{
	polynomial_t *p = NULL;
	polymorph_t *q = NULL;

	p = polynomial_init("P");
	polynomial_append(p, complex_init(9.0, 0.0), 3);
	polynomial_append(p, complex_init(4.0, 0.0), 2);
	polynomial_append(p, complex_init(1.0, 0.0), 0);

	q = polynomial_zeros(p);

	polymorph_free(q);
}
