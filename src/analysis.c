#include <stdlib.h>
#include <string.h>

#include <analysis.h>

polynomial_t *polynomial_differentiate(polynomial_t *p)
{
	polynomial_t *q = NULL;
	monomial_t *iterator = NULL;
	char *name = NULL;

	if (p == NULL)
		return NULL;

	q = polynomial_init(NULL);
	if (q == NULL)
		return NULL;

	name = (char*) malloc((sizeof(p->name) + 1) * sizeof(char));
	if (name != NULL)
	{
		strcpy(name, p->name);
		strcat(name, "'");

		q->name = name;
	}

	for (iterator = p->first ; iterator != NULL && iterator->degree > 0 ; iterator = iterator->next)
		polynomial_append(q, complex_scalarProd((double) iterator->degree, iterator->coef), iterator->degree - 1);

	return q;
}
