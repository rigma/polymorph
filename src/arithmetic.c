#include <stdlib.h>

#include <type/complex.h>
#include <type/monomial.h>
#include <arithmetic.h>

polynomial_t *polynomial_sum(polynomial_t *p, polynomial_t *q)
{
	monomial_t *a = NULL, *b = NULL;
	polynomial_t *r = NULL;
	complex_t *z = NULL;

	// Mesure de sécurité
	if (p == NULL || q == NULL)
		return NULL;

	// On initialise le polynôme de résultat et on vérifie qu'il a bien était allouer en mémoire
	r = polynomial_init(NULL);
	if (r == NULL)
		return NULL;

	// On règle les pointeurs des monômes avec leur position de départ
	a = p->first;
	b = q->first;

	// On parcourt les deux polynômes de la somme
	while (a != NULL || b != NULL)
	{
		// Si les deux adresses a et b sont différentes de NULL
		if (a != NULL && b != NULL)
		{
			// Si les monômes sont de même degré, on additionne les coefficients et on les ajoute au résultat
			if (a->degree == b->degree)
			{
				z = complex_sum(a->coef, b->coef);
				if (z == NULL)
				{
					polynomial_free(r);

					return NULL;
				}

				polynomial_append(r, z, a->degree);
				a = a->next;
				b = b->next;
			}
			// Sinon si le monôme a est de plus grand degré, on ajoute le coefficient de a au monôme
			else if (a->degree > b->degree)
			{
				z = complex_init(a->coef->re, a->coef->im);
				if (z == NULL)
				{
					polynomial_free(r);

					return NULL;
				}

				polynomial_append(r, z, a->degree);
				a = a->next;
			}
			// Sinon, on fait de même pour le coefficient de b
			else
			{
				z = complex_init(b->coef->re, b->coef->im);
				if (z == NULL)
				{
					polynomial_free(r);

					return NULL;
				}

				polynomial_append(r, z, b->degree);
				b = b->next;
			}
		}
		// S'il n'y a que l'adresse a qui est différente de NULL
		else if (a != NULL)
		{
			z = complex_init(a->coef->re, a->coef->im);
			if (z == NULL)
			{
				polynomial_free(r);

				return NULL;
			}

			// On ajoute le coefficient de a au résultat et on passe à l'élément suivant
			polynomial_append(r, z, a->degree);
			a = a->next;
		}
		// Enfin, s'il n'y a que l'adresse de b qui est différente de NULL
		else
		{
			z = complex_init(b->coef->re, b->coef->im);
			if (z == NULL)
			{
				polynomial_free(r);

				return NULL;
			}

			// On ajoute le coefficient de b au résultat et on passe à l'élément suivant
			polynomial_append(r, z, b->degree);
			b = b->next;
		}
	}

	// Finalement, on renvoit l'adresse du résultat
	return r;
}

polynomial_t *polynomial_diff(polynomial_t *p, polynomial_t *q)
{
	polynomial_t *tmp = NULL, *r = NULL;
	complex_t *k = NULL;

	// Mesure de sécurité
	if (p == NULL || q == NULL)
		return NULL;

	// On détermine -q
	k = complex_init(-1.0, 0.0);
	tmp = polynomial_scalarProduct(k, q);

	if (tmp == NULL)
	{
		complex_free(k);

		return NULL;
	}

	// Puis on détermine p + (-q)
	r = polynomial_sum(p, tmp);

	// On libère les variables temporaires
	complex_free(k);
	polynomial_free(tmp);

	// Et on retourne le résultat
	return r;
}

polynomial_t *polynomial_scalarProduct(complex_t *k, polynomial_t *p)
{
	polynomial_t *r = NULL;
	monomial_t *m = NULL;

	// Mesure de sécurité
	if (k == NULL || p == NULL)
		return NULL;

	// On initialise le polynôme résultant
	r = polynomial_init(NULL);
	if (r == NULL)
		return NULL;

	// On parcourt tous les monômes de p
	m = p->first;
	
	// Si k est un réel pur, on se contentera de faire des produits scalaires
	if (k->im == 0.0)
	{
		while (m != NULL)
		{
			polynomial_append(r, complex_scalarProd(k->re, m->coef), m->degree);
			m = m->next;
		}
	}
	// Sinon, on fera des produits "normaux" avec deux nombres complexes
	else
	{
		while (m != NULL)
		{
			polynomial_append(r, complex_prod(k, m->coef), m->degree);
			m = m->next;
		}
	}

	// On renvoit l'adresse du résultat
	return r;
}

polynomial_t *polynomial_prod(polynomial_t *p, polynomial_t *q)
{
	polynomial_t *z2 = NULL, *z1 = NULL, *z0 = NULL;
	polynomial_t *p1 = NULL, *p0 = NULL, *q1 = NULL, *q0 = NULL;
	polynomial_t *r2 = NULL, *r1 = NULL, *r0 = NULL;
	polynomial_t *tmp = NULL;
	monomial_t *iterator = NULL;
	unsigned long i = 0, n = 0;

	if (p == NULL || q == NULL)
		return NULL;

	if (p->degree == 0 && q->degree == 0)
		return polynomial_sum(p, q);
	else if (p->degree > q->degree)
	{
		n = q->degree;

		p1 = polynomial_extract(p, p->degree, q->degree);
		if (p1 == NULL)
			return NULL;

		polynomial_reduce(p1, n);

		q1 = polynomial_extract(q, q->degree, q->degree);
		if (q1 == NULL)
		{
			polynomial_free(p1);

			return NULL;
		}

		polynomial_reduce(q1, n);

		z2 = polynomial_scalarProduct(q->first->coef, p1);
		if (z2 == NULL)
		{
			polynomial_free(p1);
			polynomial_free(q1);

			return NULL;
		}
	}
	else if (p->degree < q->degree)
	{
		n = p->degree;

		p1 = polynomial_extract(p, p->degree, p->degree);
		if (p1 == NULL)
			return NULL;

		polynomial_reduce(p1, n);

		q1 = polynomial_extract(q, q->degree, p->degree);
		if (q1 == NULL)
		{
			polynomial_free(p1);

			return NULL;
		}

		polynomial_reduce(q1, n);

		z2 = polynomial_scalarProduct(p->first->coef, q1);
		if (z2 == NULL)
		{
			polynomial_free(p1);
			polynomial_free(q1);

			return NULL;
		}
	}
	else
	{
		n = p->degree;

		p1 = polynomial_extract(p, p->degree, p->degree);
		if (p1 == NULL)
			return NULL;

		polynomial_reduce(p1, n);

		q1 = polynomial_extract(q, q->degree, q->degree);
		if (q1 == NULL)
		{
			polynomial_free(p1);

			return NULL;
		}

		polynomial_reduce(q1, n);

		z2 = polynomial_init(NULL);
		if (z2 == NULL)
		{
			polynomial_free(p1);
			polynomial_free(q1);

			return NULL;
		}

		polynomial_append(z2, complex_prod(p->first->coef, q->first->coef), 0);
	}

	p0 = polynomial_extract(p, p->degree - 1, 0);
	if (p0 == NULL)
	{
		polynomial_free(p1);
		polynomial_free(q1);

		polynomial_free(z2);

		return NULL;
	}

	q0 = polynomial_extract(q, q->degree - 1, 0);
	if (q0 == NULL)
	{
		polynomial_free(p1);
		polynomial_free(p0);
		polynomial_free(q1);

		polynomial_free(z2);

		return NULL;
	}
	
	r0 = polynomial_sum(p1, p0);
	if (r0 == NULL)
	{
		polynomial_free(p1);
		polynomial_free(p0);
		polynomial_free(q1);
		polynomial_free(q0);

		polynomial_free(z2);

		return NULL;
	}

	r1 = polynomial_sum(q1, q0);
	if (r1 == NULL)
	{
		polynomial_free(p1);
		polynomial_free(p0);
		polynomial_free(q1);
		polynomial_free(q0);

		polynomial_free(z2);
		polynomial_free(r0);

		return NULL;
	}

	r2 = polynomial_prod(r1, r0);
	if (r2 == NULL)
	{
		polynomial_free(p1);
		polynomial_free(p0);
		polynomial_free(q1);
		polynomial_free(q0);

		polynomial_free(z2);
		polynomial_free(r1);
		polynomial_free(r0);

		return NULL;
	}

	polynomial_free(r1);
	polynomial_free(r0);

	z0 = polynomial_prod(p0, q0);
	if (z0 == NULL)
	{
		polynomial_free(p1);
		polynomial_free(p0);
		polynomial_free(q1);
		polynomial_free(q0);

		polynomial_free(z2);
		polynomial_free(r2);

		return NULL;
	}

	polynomial_free(p1);
	polynomial_free(p0);
	polynomial_free(q1);
	polynomial_free(q0);

	z1 = polynomial_diff(r2, z2);
	if (z1 == NULL)
	{
		polynomial_free(r2);
		polynomial_free(z2);
		polynomial_free(z1);
		polynomial_free(z0);

		return NULL;
	}

	tmp = polynomial_diff(z1, z0);
	if (tmp == NULL)
	{
		polynomial_free(r2);
		polynomial_free(z2);
		polynomial_free(z1);
		polynomial_free(z0);

		return NULL;
	}

	polynomial_free(z1);
	z1 = tmp;

	polynomial_increase(z2, 2 * n);
	polynomial_increase(z1, n);

	tmp = polynomial_sum(z2, z1);
	if (tmp == NULL)
	{
		polynomial_free(r2);
		polynomial_free(z2);
		polynomial_free(z1);
		polynomial_free(z0);

		return NULL;
	}

	polynomial_free(z2);
	z2 = tmp;

	tmp = polynomial_sum(z2, z0);
	if (tmp == NULL)
	{
		polynomial_free(r2);
		polynomial_free(z2);
		polynomial_free(z1);
		polynomial_free(z0);

		return NULL;
	}

	polynomial_free(z2);
	z2 = tmp;

	polynomial_free(r2);
	polynomial_free(z1);
	polynomial_free(z0);

	return z2;
}
