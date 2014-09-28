#include <stdlib.h>

#include <type/complex.h>
#include <type/monomial.h>
#include <arithmetic.h>

polynomial_t *polynomial_sum(polynomial_t *p, polynomial_t *q)
{
	monomial_t *a = NULL, *b = NULL;
	polynomial_t *r = NULL;

	// Mesure de s�curit�
	if (p == NULL || q == NULL)
		return NULL;

	// On initialise le polyn�me de r�sultat et on v�rifie qu'il a bien �tait allouer en m�moire
	r = polynomial_init(NULL);
	if (r == NULL)
		return NULL;

	// On r�gle les pointeurs des mon�mes avec leur position de d�part
	a = p->first;
	b = q->first;

	// On parcourt les deux polyn�mes de la somme
	while (a != NULL || b != NULL)
	{
		// Si les deux adresses a et b sont diff�rentes de NULL
		if (a != NULL && b != NULL)
		{
			// Si les mon�mes sont de m�me degr�, on additionne les coefficients et on les ajoute au r�sultat
			if (a->degree == b->degree)
			{
				polynomial_append(r, complex_sum(a->coef, b->coef), a->degree);
				a = a->next;
				b = b->next;
			}
			// Sinon si le mon�me a est de plus grand degr�, on ajoute le coefficient de a au mon�me
			else if (a->degree > b->degree)
			{
				polynomial_append(r, a->coef, a->degree);
				a = a->next;
			}
			// Sinon, on fait de m�me pour le coefficient de b
			else
			{
				polynomial_append(r, b->coef, b->degree);
				b = b->next;
			}
		}
		// S'il n'y a que l'adresse a qui est diff�rente de NULL
		else if (a != NULL)
		{
			// On ajoute le coefficient de a au r�sultat et on passe � l'�l�ment suivant
			polynomial_append(r, a->coef, a->degree);
			a = a->next;
		}
		// Enfin, s'il n'y a que l'adresse de b qui est diff�rente de NULL
		else
		{
			// On ajoute le coefficient de b au r�sultat et on passe � l'�l�ment suivant
			polynomial_append(r, b->coef, b->degree);
			b = b->next;
		}
	}

	// Finalement, on renvoit l'adresse du r�sultat
	return r;
}

polynomial_t *polynomial_diff(polynomial_t *p, polynomial_t *q)
{
	polynomial_t *tmp = NULL, *r = NULL;
	complex_t *k = NULL;

	// Mesure de s�curit�
	if (p == NULL || q == NULL)
		return NULL;

	// On d�termine -q
	k = complex_init(-1.0, 0.0);
	tmp = polynomial_scalarProduct(k, q);

	if (tmp == NULL)
	{
		complex_free(k);

		return NULL;
	}

	// Puis on d�termine p + (-q)
	r = polynomial_sum(p, tmp);

	// On lib�re les variables temporaires
	complex_free(k);
	polynomial_free(tmp);

	// Et on retourne le r�sultat
	return r;
}

polynomial_t *polynomial_scalarProduct(complex_t *k, polynomial_t *p)
{
	polynomial_t *r = NULL;
	monomial_t *m = NULL;

	// Mesure de s�curit�
	if (k == NULL || p == NULL)
		return NULL;

	// On initialise le polyn�me r�sultant
	r = polynomial_init(NULL);
	if (r == NULL)
		return NULL;

	// On parcourt tous les mon�mes de p
	m = p->first;
	
	// Si k est un r�el pur, on se contentera de faire des produits scalaires
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

	// On renvoit l'adresse du r�sultat
	return r;
}