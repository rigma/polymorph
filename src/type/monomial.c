#include <stdlib.h>
#include <math.h>

#include <type/monomial.h>

monomial_t *monomial_init(complex_t *coef, unsigned long pow)
{
	monomial_t *m = NULL;

	if (coef == NULL)
		return NULL;

	m = (monomial_t*) malloc(sizeof(monomial_t));
	if (m == NULL)
		return NULL;

	m->coef = coef;
	m->pow = pow;
	m->previous = NULL;
	m->next = NULL;

	return m;
}

void monomial_free(monomial_t *m)
{
	complex_free(m->coef);
	free(m);
}

complex_t *monomial_eval(monomial_t *m, double x)
{
	return complex_scalarProd(pow(x, (double) m->pow), m->coef);
}
