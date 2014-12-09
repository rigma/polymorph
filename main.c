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
	console_start("msg.txt");
	
	return EXIT_SUCCESS;
}

void test()
{
	polynomial_t *p = NULL, *q = NULL, *r = NULL;

	p = polynomial_init("P");
	polynomial_append(p, complex_init(9.0, 0.0), 2);
	polynomial_append(p, complex_init(4.0, 0.0), 1);
	polynomial_append(p, complex_init(1.0, 0.0), 0);

	q = polynomial_init("Q");
	polynomial_append(q, complex_init(3.0, 2.0), 2);
	polynomial_append(q, complex_init(2.0, 1.0), 1);
	polynomial_append(q, complex_init(1.0, 0.0), 0);

	polynomial_display(p);
	fprintf(stdout, "\n");
	polynomial_display(q);
	fprintf(stdout, "\n");

	fprintf(stdout, "Addition : ");
	r = polynomial_sum(p, q, "R");

	polynomial_display(r);
	fprintf(stdout, "\n");
	polynomial_free(r);

	fprintf(stdout, "Soustraction : ");
	r = polynomial_diff(p, q, "R");

	polynomial_display(r);
	fprintf(stdout, "\n");
	polynomial_free(r);

	fprintf(stdout, "Multiplication : ");
	r = polynomial_prod(p, q, "R");

	polynomial_display(r);
	fprintf(stdout, "\n");
	polynomial_free(r);

	polynomial_free(p);
	polynomial_free(q);

	system("pause");
}
