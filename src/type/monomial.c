#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <type/monomial.h>

monomial_t *monomial_init(complex_t *coef, unsigned long degree)
{
	monomial_t *m = NULL;

	if (coef == NULL)
		return NULL;

	m = (monomial_t*) malloc(sizeof(monomial_t));
	if (m == NULL)
		return NULL;

	m->coef = coef;
	m->degree = degree;
	m->previous = NULL;
	m->next = NULL;

	return m;
}

void monomial_free(monomial_t *m)
{
	complex_free(m->coef);
	free(m);
}

void monomial_display(monomial_t *m)
{
	char *z = NULL;

	if (m == NULL)
		return;

	z = complex_display(m->coef, 0);

	if (m->degree > 0)
	{
	    if (m->coef->re == 0 && m->coef->re == 0);
	    else if (m->coef->re > 0)
        {
            printf("%s * X ^ %lu", z, m->degree);
        }
        else if (m->coef->im > 0)
        {
            printf("%s * X ^ %lu", z, m->degree);
        }
        else if (m->coef->re > 0 && m->coef->im > 0)
        {
            printf("%s * X ^ %lu", z, m->degree);
        }
	    else
            printf("(%s) * X ^ %lu", z, m->degree);
	}

	else
		printf("%s", z);

	free(z);
}

complex_t *monomial_eval(monomial_t *m, double x)
{
	return complex_scalarProd(pow(x, (double) m->degree), m->coef);
}
