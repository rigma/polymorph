#include <stdlib.h>

#include <type/complex.h>
#include <type/monomial.h>
#include <arithmetic.h>

polynomial_t *polynomial_sum(polynomial_t *p, polynomial_t *q)
{
	monomial_t *a = NULL, *b = NULL;
	polynomial_t *r = NULL;

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
				polynomial_append(r, complex_sum(a->coef, b->coef), a->degree);
				a = a->next;
				b = b->next;
			}
			// Sinon si le monôme a est de plus grand degré, on ajoute le coefficient de a au monôme
			else if (a->degree > b->degree)
			{
				polynomial_append(r, a->coef, a->degree);
				a = a->next;
			}
			// Sinon, on fait de même pour le coefficient de b
			else
			{
				polynomial_append(r, b->coef, b->degree);
				b = b->next;
			}
		}
		// S'il n'y a que l'adresse a qui est différente de NULL
		else if (a != NULL)
		{
			// On ajoute le coefficient de a au résultat et on passe à l'élément suivant
			polynomial_append(r, a->coef, a->degree);
			a = a->next;
		}
		// Enfin, s'il n'y a que l'adresse de b qui est différente de NULL
		else
		{
			// On ajoute le coefficient de b au résultat et on passe à l'élément suivant
			polynomial_append(r, b->coef, b->degree);
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
