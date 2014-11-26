#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include <type/complex.h>
#include <type/polymorph.h>
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

complex_t **polynomial_zeros_DurandKerner(polynomial_t *p)
{
	complex_t **roots = NULL, **previous = NULL, **coefs = NULL;
	complex_t *result = NULL, *eval = NULL, *delta = NULL, *tmp1 = NULL, *tmp2 = NULL;
	monomial_t *iterator = NULL;
	unsigned long i = 0, j = 0, k = 0;
	short count = 0;
	char stable = 0;
	char back = 0;

	// Mesure de sécurité
	if (p == NULL)
		return NULL;

	// On récupère d'abord les coefficients du polynôme
	coefs = (complex_t**) calloc(p->degree + 1, sizeof(complex_t*));
	if (coefs == NULL)
		return NULL;

	for (iterator = p->first, i = 0 ; iterator != NULL ; iterator = iterator->next, i++)
	{
		if (iterator->previous != NULL && iterator->previous->degree - iterator->degree > 1 && !back)
		{
			coefs[i] = complex_init(0.0, 0.0);
			iterator = iterator->previous;
			back = 1;
		}
		else
		{
			coefs[i] = complex_init(iterator->coef->re, iterator->coef->im);
			back = 0;
		}

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
			for (i = 0 ; i < p->degree + 1 ; i++)
				complex_free(coefs[i]);

			free(coefs);
		}

		// On divise tous les autres coefficients par ce dernier
		for (i = 0 ; i < p->degree ; i++)
		{
			tmp2 = complex_div(coefs[i], tmp1);
			if (tmp2 == NULL)
			{
				for (j = 0 ; j < p->degree + 1 ; j++)
					complex_free(coefs[i]);

				complex_free(tmp1);
				free(coefs);

				return NULL;
			}

			complex_free(coefs[i]);
			coefs[i] = tmp2;
		}
	}

	complex_free(tmp1);

	// On initialise les tableaux qui contiennent des approximations des racines
	roots = (complex_t**) calloc(p->degree, sizeof(complex_t*));
	if (roots == NULL)
	{
		for (i = 0 ; i < p->degree + 1 ; i++)
			complex_free(coefs[i]);

		free(coefs);

		return NULL;
	}

	previous = (complex_t**) calloc(p->degree, sizeof(complex_t*));
	if (previous == NULL)
	{
		for (i = 0 ; i < p->degree + 1 ; i++)
			complex_free(coefs[i]);

		free(coefs);
		free(roots);

		return NULL;
	}

	tmp1 = complex_init(0.4, 0.9);
	if (tmp1 == NULL)
	{
		for (i = 0 ; i < p->degree + 1; i++)
			complex_free(coefs[i]);

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
			for (j = 0 ; j < p->degree + 1 ; j++)
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
	while (!stable && count < ROOTS_MAX_COUNT)
	{
		stable = 1;

		// On copie les anciennes approximations pour la récurrence
		memcpy(previous, roots, p->degree * sizeof(complex_t*));

		// Pour chaque approximation
		for (i = 0 ; i < p->degree ; i++)
		{
			result = complex_init(1.0, 0.0);

			// On effectue :  x_n = x_{n - 1} - \frac{f(x_{n - 1})}{\prod_{i \neq j} (x_i - x_j)}
			for (j = 0 ; j < p->degree ; j++)
			{
				if (i != j)
				{
					tmp1 = complex_diff(previous[i], previous[j]);
					if (tmp1 == NULL)
					{
						complex_free(result);

						for (k = 0 ; k < p->degree + 1 ; k++)
							complex_free(coefs[k]);

						for (k = 0 ; k < p->degree ; k++)
						{
							complex_free(roots[k]);
							complex_free(previous[k]);
						}

						free(coefs);
						free(roots);
						free(previous);

						return NULL;
					}

					tmp2 = complex_prod(tmp1, result);
					if (tmp2 == NULL)
					{
						complex_free(result);

						for (k = 0 ; k < p->degree + 1 ; k++)
							complex_free(coefs[k]);

						for (k = 0 ; k < p->degree ; k++)
						{
							complex_free(roots[k]);
							complex_free(previous[k]);
						}

						free(coefs);
						free(roots);
						free(previous);

						return NULL;
					}

					complex_free(tmp1);
					complex_free(result);

					result = tmp2;
				}
			}

			tmp1 = complex_init(1.0, 0.0);
			eval = polymorph_evalFromTable(tmp1, p->degree, previous, previous[i]);
			if (eval == NULL)
			{
				complex_free(tmp1);
				complex_free(result);

				for (k = 0 ; k < p->degree + 1 ; k++)
					complex_free(coefs[k]);

				for (k = 0 ; k < p->degree ; k++)
				{
					complex_free(roots[k]);
					complex_free(previous[k]);
				}

				free(coefs);
				free(roots);
				free(previous);

				return NULL;
			}

			complex_free(tmp1);

			roots[i] = complex_div(eval, result);
			if (roots[i] == NULL)
			{
				complex_free(eval);
				complex_free(result);

				for (k = 0 ; k < p->degree + 1 ; k++)
					complex_free(coefs[k]);

				for (k = 0 ; k < p->degree ; k++)
				{
					complex_free(roots[k]);
					complex_free(previous[k]);
				}

				free(coefs);
				free(roots);
				free(previous);

				return NULL;
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
			{
				for (k = 0 ; k < p->degree + 1 ; k++)
					complex_free(coefs[k]);

				for (k = 0 ; k < p->degree ; k++)
				{
					complex_free(roots[k]);
					complex_free(previous[k]);
				}

				free(coefs);
				free(roots);
				free(previous);

				return NULL;
			}

			stable &= (delta->mod < ROOTS_EPSILON);
			complex_free(delta);
		}
	}

	// Puis on renvoit les résultats
	for (i = 0 ; i < p->degree + 1 ; i++)
		complex_free(coefs[i]);

	for (i = 0 ; i < p->degree ; i++)
		complex_free(previous[i]);

	return roots;
}

polymorph_t *polynomial_zeros(polynomial_t *p)
{
	polymorph_t *result = NULL;
	polynomial_t *q = NULL;
	complex_t **roots = NULL;
	complex_t *offset = NULL, *num = NULL, *denom = NULL, *a = NULL, *b = NULL, *tmp = NULL;
	char *str = NULL;
	unsigned long i = 0, j = 0;
	unsigned short count = 0;
	unsigned char stable = 1;

	if (p == NULL)
		return NULL;
	
	// On dérive le polynôme p
	q = polynomial_differentiate(p);
	if (q == NULL)
		return NULL;

	// On approxime une première fois les racines
	roots = polynomial_zeros_DurandKerner(p);
	if (roots == NULL)
	{
		polynomial_free(q);

		return NULL;
	}

	while (!stable && count < ROOTS_MAX_COUNT)
	{
		stable = 1;

		for (i = 0; i < p->degree; i++)
		{
			a = polynomial_eval(p, p->first->coef, p->first->next, roots[i]);
			if (a == NULL)
			{
				polynomial_free(q);

				for (i = 0; i < p->degree; i++)
					complex_free(roots[i]);

				free(roots);

				return NULL;
			}

			b = polynomial_eval(q, q->first->coef, q->first->next, roots[i]);
			if (b == NULL)
			{
				polynomial_free(q);
				complex_free(a);

				for (i = 0; i < p->degree; i++)
					complex_free(roots[i]);

				free(roots);

				return NULL;
			}

			// On fait la division de P(z_k) par P'(z_k)
			num = complex_div(a, b);
			if (num == NULL)
			{
				polynomial_free(q);
				complex_free(a);
				complex_free(b);

				for (i = 0; i < p->degree; i++)
					complex_free(roots[i]);

				free(roots);

				return NULL;
			}

			// On libère a et b car, on en n'a plus besoin
			complex_free(a);
			complex_free(b);

			a = NULL;
			b = NULL;

			// On prépare le diviseur
			denom = complex_init(1.0, 0.0);
			if (denom == NULL)
			{
				polynomial_free(q);
				complex_free(num);

				for (i = 0; i < p->degree; i++)
					complex_free(roots[i]);

				free(roots);

				return NULL;
			}

			a = complex_init(0.0, 0.0);
			if (a == NULL)
			{
				polynomial_free(q);
				complex_free(num);
				complex_free(denom);

				for (i = 0; i < p->degree; i++)
					complex_free(roots[i]);

				free(roots);

				return NULL;
			}

			for (j = 0; j < p->degree; j++)
			{
				if (i != j)
				{
					b = complex_diff(roots[i], roots[j]);
					if (b == NULL)
					{
						polynomial_free(q);
						complex_free(a);
						complex_free(num);
						complex_free(denom);

						for (i = 0; i < p->degree; i++)
							complex_free(roots[i]);

						free(roots);

						return NULL;
					}

					tmp = complex_reverse(b);
					if (tmp == NULL)
					{
						polynomial_free(q);
						complex_free(a);
						complex_free(b);
						complex_free(num);
						complex_free(denom);

						for (i = 0; i < p->degree; i++)
							complex_free(roots[i]);

						free(roots);

						return NULL;
					}

					complex_free(b);
					b = tmp;

					tmp = complex_sum(a, b);
					if (tmp == NULL)
					{
						polynomial_free(q);
						complex_free(a);
						complex_free(b);
						complex_free(num);
						complex_free(denom);

						for (i = 0; i < p->degree; i++)
							complex_free(roots[i]);

						free(roots);

						return NULL;
					}
				}

				a = tmp;
				complex_free(b);
			}

			// On multiplie la somme par le numérateur
			tmp = complex_prod(num, a);
			if (tmp == NULL)
			{
				polynomial_free(q);
				complex_free(a);
				complex_free(num);
				complex_free(denom);

				for (i = 0; i < p->degree; i++)
					complex_free(roots[i]);

				free(roots);

				return NULL;
			}

			complex_free(a);
			a = tmp;

			// Puis on termine la préparation du dénominateur
			tmp = complex_diff(denom, a);
			if (tmp == NULL)
			{
				polynomial_free(q);
				complex_free(a);
				complex_free(num);
				complex_free(denom);

				for (i = 0; i < p->degree; i++)
					complex_free(roots[i]);

				free(roots);

				return NULL;
			}

			complex_free(a);
			complex_free(denom);
			denom = tmp;

			// On fait la division et on multiplie par et on soustrait le résultat de la racine de départ
			offset = complex_div(num, denom);
			if (offset == NULL)
			{
				polynomial_free(q);
				complex_free(num);
				complex_free(denom);

				for (i = 0; i < p->degree; i++)
					complex_free(roots[i]);

				free(roots);

				return NULL;
			}

			complex_free(num);
			complex_free(denom);

			tmp = complex_diff(roots[i], offset);
			if (tmp == NULL)
			{
				polynomial_free(q);
				complex_free(offset);

				for (i = 0; i < p->degree; i++)
					complex_free(roots[i]);

				free(roots);

				return NULL;
			}

			complex_free(offset);
			complex_free(roots[i]);
			roots[i] = tmp;

			stable &= (roots[i]->mod < ROOTS_EPSILON);
		}
	}

	// On libère la dérivée
	polynomial_free(q);

	// On prépare le polynôme de résultat
	result = (polymorph_t*) polymorph_init(p->name);
	if (result == NULL)
	{
		for (i = 0 ; i < p->degree ; i++)
			complex_free(roots[i]);

		free(roots);

		return NULL;
	}

	result->a = complex_init(p->first->coef->re, p->first->coef->im);
	for (i = 0 ; i < p->degree ; i++)
		polymorph_append(result, roots[i]);

	polynomial_free(p);
	free(roots);

	return result;
}
