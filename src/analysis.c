#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <type/complex.h>
#include <type/polymorph.h>
#include <analysis.h>

#define MAX_COUNT 999
#define EPSILON   1e-15

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

complex_t **polynomial_zeros_DurandKerner(polynomial_t *p)
{
	complex_t **roots = NULL, **previous = NULL, **coefs = NULL;
	complex_t *result = NULL, *eval = NULL, *delta = NULL, *tmp1 = NULL, *tmp2 = NULL;
	monomial_t *iterator = NULL;
	unsigned long i = 0, j = 0;
	short count = 0;
	char stable = 0;

	// Mesure de sécurité
	if (p == NULL)
		return NULL;

	// On récupère d'abord les coefficients du polynôme
	coefs = (complex_t**) calloc(p->degree, sizeof(complex_t*));
	if (coefs == NULL)
		return NULL;

	for (iterator = p->first->next, i = 0 ; iterator != NULL ; iterator = iterator->next, i++)
	{
		coefs[i] = complex_init(iterator->coef->re, iterator->coef->im);
		if (coefs[i] == NULL)
		{
			for (j = 0 ; i < j ; j++)
				complex_free(coefs[i]);

			free(coefs);
		}
	}

	// Si le coefficient dominant est différent de 1
	tmp1 = complex_init(1.0, 0.0);

	if (!complex_compare(coefs[0], tmp1))
	{
		complex_free(tmp1);
		tmp1 = complex_init(coefs[0]->re, coefs[0]->im);
		if (tmp1 == NULL)
		{
			for (i = 0; i < p->degree; i++)
				complex_free(coefs[i]);

			free(coefs);
		}

		// On divise tous les autres coefficients par ce dernier
		for (i = 0 ; i < p->degree ; i++)
		{
			tmp2 = complex_div(coefs[i], tmp1);
			if (tmp2 == NULL)
			{
				for (j = 0 ; j < p->degree ; j++)
					complex_free(coefs[i]);

				complex_free(tmp1);
				free(coefs);

				return NULL;
			}

			coefs[i] = tmp2;
		}
	}

	complex_free(tmp1);

	// On initialise les tableaux qui contiennent des approximations des racines
	roots = (complex_t**) calloc(p->degree, sizeof(complex_t*));
	if (roots == NULL)
	{
		for (i = 0 ; i < p->degree ; i++)
			complex_free(coefs[i]);

		free(coefs);

		return NULL;
	}

	previous = (complex_t**) calloc(p->degree, sizeof(complex_t*));
	if (previous == NULL)
	{
		for (i = 0 ; i < p->degree ; i++)
			complex_free(coefs[i]);

		free(coefs);
		free(roots);

		return NULL;
	}

	tmp1 = complex_init(0.4, 0.9);
	if (tmp1 == NULL)
	{
		free(roots);
		free(previous);

		return NULL;
	}

	// On initialise toutes les approximations à 0.4 + 0.9i
	for (i = 0 ; i < p->degree ; i++)
	{
		roots[i] = complex_pow(tmp1, i);
		if (roots[i] == NULL)
		{
			for (j = 0 ; j < p->degree ; j++)
				complex_free(coefs[i]);

			for (j = 0 ; j < i ; j++)
				complex_free(roots[j]);

			free(coefs);
			free(roots);
			free(previous);

			return NULL;
		}
	}

	// Tant qu'on a pas itéré 999 fois et que l'approximation n'est pas stable
	count = 0;
	while (!stable && count < MAX_COUNT)
	{
		// On copie les anciennes approximations pour la récurrence
		memcpy(previous, roots, p->degree * sizeof(complex_t*));

		// Pour chaque approximation
		for (i = 0; i < p->degree; i++)
		{
			result = complex_init(1.0, 0.0);

			// On effectue :  x_n = x_{n - 1} - \frac{f(x_{n - 1})}{\prod_{n \neq i} (x_{n - 1} - x_i)}
			for (j = 0; j < p->degree; j++)
			{
				if (i != j)
				{
					tmp1 = complex_diff(previous[i], previous[j]);
					if (tmp1 == NULL)
					{
						complex_free(result);

						goto error;
					}

					tmp2 = complex_prod(tmp1, result);
					if (tmp2 == NULL)
					{
						complex_free(result);

						goto error;
					}

					complex_free(tmp1);
					complex_free(result);

					result = tmp2;
					complex_free(tmp2);
				}
			}

			tmp1 = complex_init(1.0, 0.0);
			eval = polymorph_evalFromTable(tmp1, coefs, previous[i]);
			if (eval == NULL)
			{
				complex_free(result);

				goto error;
			}

			roots[i] = complex_div(eval, result);
			if (roots[i] == NULL)
			{
				complex_free(result);

				goto error;
			}

			complex_free(eval);
			complex_free(result);
		}

		// On incrémente le compteur d'itérations
		count++;

		// Puis on regarde si l'approximation se stabilise pour chaque approximation
		for (i = 0 ; i < p->degree ; i++)
		{
			delta = complex_diff(roots[i], previous[i]);
			if (delta == NULL)
				goto error;

			stable &= (fabs(delta->re) < EPSILON) && (fabs(delta->im) < EPSILON);
			complex_free(delta);
		}
	}

	// Puis on renvoit les résultats
	for (i = 0 ; i < p->degree ; i++)
	{
		complex_free(coefs[i]);
		complex_free(previous[i]);
	}

	return roots;

error:
	for (i = 0 ; i < p->degree ; i++)
	{
		complex_free(coefs[i]);
		complex_free(roots[i]);
		complex_free(previous[i]);
	}

	free(coefs);
	free(roots);
	free(previous);

	return NULL;
}

polymorph_t *polynomial_zeros(polynomial_t *p)
{
	if (p == NULL)
		return NULL;

	return NULL;
}
