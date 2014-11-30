#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <type/complex.h>
#include <type/monomial.h>
#include <arithmetic.h>

polynomial_t *polynomial_sum(polynomial_t *p, polynomial_t *q, const char *name)
{
	monomial_t *a = NULL, *b = NULL;
	polynomial_t *r = NULL;
	complex_t *z = NULL;
	char *str = NULL;

	// Mesure de sécurité
	if (p == NULL || q == NULL)
		return NULL;

	// On initialise le polynôme de résultat et on vérifie qu'il a bien était allouer en mémoire
	if (name != NULL)
		r = polynomial_init(name);
	else if (p->name != NULL && q->name != NULL)
	{
		str = (char*) malloc((sizeof(p->name) + sizeof(q->name) + 6) * sizeof(char));

		if (str == NULL)
			r = polynomial_init(str);
		else
		{
			strcpy(str, "(");
			strcat(str, p->name);
			strcat(str, " + ");
			strcat(str, q->name);
			strcat(str, ")");

			r = polynomial_init(str);
		}
	}
	else
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

polynomial_t *polynomial_diff(polynomial_t *p, polynomial_t *q, const char *name)
{
	polynomial_t *tmp = NULL, *r = NULL;
	complex_t *k = NULL;
	char *str = NULL;

	// Mesure de sécurité
	if (p == NULL || q == NULL)
		return NULL;

	// On détermine -q
	k = complex_init(-1.0, 0.0);
	tmp = polynomial_scalarProduct(k, q, NULL);

	if (tmp == NULL)
	{
		complex_free(k);

		return NULL;
	}

	// Puis on détermine p + (-q)
	if (name != NULL)
		r = polynomial_sum(p, tmp, name);
	else if (p->name != NULL && q->name != NULL)
	{
		str = (char*) malloc((sizeof(p->name) + sizeof(q->name) + 6) * sizeof(char));
		if (str == NULL)
			r = polynomial_sum(p, tmp, NULL);
		else
		{
			strcpy(str, "(");
			strcat(str, p->name);
			strcat(str, " - ");
			strcat(str, q->name);
			strcat(str, ")");

			r = polynomial_sum(p, tmp, str);
		}
	}
	else
		r = polynomial_sum(p, tmp, NULL);

	// On libère les variables temporaires
	complex_free(k);
	polynomial_free(tmp);

	// Et on retourne le résultat
	return r;
}

polynomial_t *polynomial_scalarProduct(complex_t *k, polynomial_t *p, const char *name)
{
	polynomial_t *r = NULL;
	monomial_t *m = NULL;
	char *str = NULL, *z = NULL;

	// Mesure de sécurité
	if (k == NULL || p == NULL)
		return NULL;

	// On initialise le polynôme résultant
	if (name != NULL)
		r = polynomial_init(name);
	else if (p->name != NULL)
	{
		z = complex_toString(k, 0);
		if (z == NULL)
			return NULL;

		if (k->re != 0.0 && k->im != 0.0)
			str = (char*) malloc((sizeof(p->name) + sizeof(z) + 8) * sizeof(char));
		else
			str = (char*) malloc((sizeof(p->name) + sizeof(z) + 6) * sizeof(char));
		
		if (str == NULL)
			return NULL;

		strcpy(str, "(");
		strcat(str, z);
		strcat(str, ") x ");
		strcat(str, p->name);

		free(z);
		z = NULL;

		r = polynomial_init(str);
	}
	else
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

polynomial_t *polynomial_prod(polynomial_t *p, polynomial_t *q, const char *name)
{
	polynomial_t *z2 = NULL, *z1 = NULL, *z0 = NULL;
	polynomial_t *p1 = NULL, *p0 = NULL, *q1 = NULL, *q0 = NULL;
	polynomial_t *r2 = NULL, *r1 = NULL, *r0 = NULL;
	polynomial_t *tmp = NULL;
	char *str = NULL;
	unsigned long n = 0;

	// Si les degrés des deux arguments sont nuls
	if (p->degree == 0 && q->degree == 0)
	{
		// On initialise le complexe de résultat
		z2 = polynomial_init(NULL);
		if (z2 == NULL)
			return NULL;

		// Et on effectue simplement p * q
		polynomial_append(z2, complex_prod(p->first->coef, q->first->coef), 0);
		
		// Et on définit le nom du polynôme final
		if (name != NULL)
		{
			z2->name = (char*) malloc(sizeof(name) * sizeof(char));
			if (z2->name != NULL)
				strcpy(z2->name, name);
		}
		else if (p->name != NULL && q->name != NULL)
		{
			str = (char*) malloc((sizeof(p->name) + sizeof(q->name) + 6) * sizeof(char));
			if (str != NULL)
			{
				strcpy(str, "(");
				strcat(str, p->name);
				strcat(str, " x ");
				strcat(str, q->name);
				strcat(str, ")");

				z2->name = str;
			}
		}

		return z2;
	}
	// Sinon si seulement un seul des polynôme est de degré nul, on réalise simplement un produit scalaire
	else if (p->degree == 0)
		return polynomial_scalarProduct(p->first->coef, q, name);
	else if (q->degree == 0)
		return polynomial_scalarProduct(q->first->coef, p, name);
	// Sinon si, le polynôme p est de plus grand degré
	else if (p->degree > q->degree)
	{
		// On mémorise le degré de q
		n = q->degree;

		// On extrait du polynôme p p1 qui va de X^(p->degree) à X^n
		p1 = polynomial_extract(p, p->degree, n);
		if (p1 == NULL)
			return NULL;

		// On le factorise par X^n
		polynomial_reduce(p1, n);

		// On fait de même avec le polynôme q
		q1 = polynomial_extract(q, q->degree, n);
		if (q1 == NULL)
		{
			polynomial_free(p1);

			return NULL;
		}

		// On factorise le polynôme extrait par X^n
		polynomial_reduce(q1, n);

		// On réalise le produit scalaire q1 x p1
		z2 = polynomial_scalarProduct(q1->first->coef, p1, NULL);
		if (z2 == NULL)
		{
			polynomial_free(p1);
			polynomial_free(q1);

			return NULL;
		}
	}
	// Sinon si q est le polynôme de plus grand degré
	else if (p->degree < q->degree)
	{
		// Même traitement que précédemment sauf que n = p->degree
		n = p->degree;

		p1 = polynomial_extract(p, p->degree, n);
		if (p1 == NULL)
			return NULL;

		polynomial_reduce(p1, n);

		q1 = polynomial_extract(q, q->degree, n);
		if (q1 == NULL)
		{
			polynomial_free(p1);

			return NULL;
		}

		polynomial_reduce(q1, n);

		z2 = polynomial_scalarProduct(p1->first->coef, q1, NULL);
		if (z2 == NULL)
		{
			polynomial_free(p1);
			polynomial_free(q1);

			return NULL;
		}
	}
	// Sinon, on a le cas général
	else
	{
		// Même traitement que pour p->degree > q->degree
		n = p->degree;

		p1 = polynomial_extract(p, p->degree, n);
		if (p1 == NULL)
			return NULL;

		polynomial_reduce(p1, n);

		q1 = polynomial_extract(q, q->degree, n);
		if (q1 == NULL)
		{
			polynomial_free(p1);

			return NULL;
		}

		polynomial_reduce(q1, n);

		// On initialise par contre un nouveau polynôme nommé z2
		z2 = polynomial_init(NULL);
		if (z2 == NULL)
		{
			polynomial_free(p1);
			polynomial_free(q1);

			return NULL;
		}

		// Et on lui ajoute comme monôme p1 x q1 au degré 0 (car factorisation par X^n)
		polynomial_append(z2, complex_prod(p1->first->coef, q1->first->coef), 0);
	}

	// On extrait ensuite les polynômes p0 et q0 qui vont de X^(n-1) à 1
	p0 = polynomial_extract(p, n - 1, 0);
	if (p0 == NULL)
	{
		polynomial_free(z2);
		polynomial_free(p1);
		polynomial_free(q1);

		return NULL;
	}

	q0 = polynomial_extract(q, n - 1, 0);
	if (q0 == NULL)
	{
		polynomial_free(z2);
		polynomial_free(p1);
		polynomial_free(p0);
		polynomial_free(q1);

		return NULL;
	}

	// On rappelle la fonction pour le produit p0 x q0 pour mieux régner
	z0 = polynomial_prod(p0, q0, NULL);
	if (z0 == NULL)
	{
		polynomial_free(z2);
		polynomial_free(p1);
		polynomial_free(p0);
		polynomial_free(q1);
		polynomial_free(q0);

		return NULL;
	}

	// On détermine p1 + p0
	r1 = polynomial_sum(p1, p0, NULL);
	if (r1 == NULL)
	{
		polynomial_free(z2);
		polynomial_free(z0);
		polynomial_free(p1);
		polynomial_free(p0);
		polynomial_free(q1);
		polynomial_free(q0);

		return NULL;
	}

	// On détermine q1 + q0
	r0 = polynomial_sum(q1, q0, NULL);
	if (r0 == NULL)
	{
		polynomial_free(z2);
		polynomial_free(z0);
		polynomial_free(r1);
		polynomial_free(p1);
		polynomial_free(p0);
		polynomial_free(q1);
		polynomial_free(q0);

		return NULL;
	}

	// On rappelle la fonction pour effectuer r1 x r0 pour mieux régner
	r2 = polynomial_prod(r1, r0, NULL);
	if (r2 == NULL)
	{
		polynomial_free(z2);
		polynomial_free(z0);
		polynomial_free(r1);
		polynomial_free(r0);
		polynomial_free(p1);
		polynomial_free(p0);
		polynomial_free(q1);
		polynomial_free(q0);

		return NULL;
	}

	// On libère de la mémoire les polynômes qui ne sont plus utiles
	polynomial_free(r1);
	polynomial_free(r0);
	polynomial_free(p1);
	polynomial_free(p0);
	polynomial_free(q1);
	polynomial_free(q0);

	// On détermine z1 = (p1 + p0)(q1 + q0) - z2 - z1
	z1 = polynomial_diff(r2, z2, NULL);
	if (z1 == NULL)
	{
		polynomial_free(r2);
		polynomial_free(z2);
		polynomial_free(z0);

		return NULL;
	}

	polynomial_free(r2);

	tmp = polynomial_diff(z1, z0, NULL);
	if (tmp == NULL)
	{
		polynomial_free(z2);
		polynomial_free(z1);
		polynomial_free(z0);

		return NULL;
	}

	polynomial_free(z1);
	z1 = tmp;

	// On distribue X^2n dans z2 et X^n dans z1
	polynomial_increase(z2, 2 * n);
	polynomial_increase(z1, n);

	// Puis on somme les polynômes obtenus pour obtenir z2 x X^2n + z1 x X^n + z0 = p x q
	tmp = polynomial_sum(z2, z1, NULL);
	if (tmp == NULL)
	{
		polynomial_free(z2);
		polynomial_free(z1);
		polynomial_free(z0);

		return NULL;
	}

	polynomial_free(z2);
	z2 = tmp;

	tmp = polynomial_sum(z2, z0, NULL);
	if (tmp == NULL)
	{
		polynomial_free(z2);
		polynomial_free(z1);
		polynomial_free(z0);

		return NULL;
	}

	polynomial_free(z2);
	z2 = tmp;

	// On définit le nom du polynôme final
	if (name != NULL)
	{
		z2->name = (char*) malloc(sizeof(name) * sizeof(char));
		if (z2->name != NULL)
			strcpy(z2->name, name);
	}
	else if (p->name != NULL && q->name != NULL)
	{
		str = (char*) malloc((sizeof(p->name) + sizeof(q->name) + 6) * sizeof(char));
		if (str != NULL)
		{
			strcpy(str, "(");
			strcat(str, p->name);
			strcat(str, " x ");
			strcat(str, q->name);
			strcat(str, ")");

			z2->name = str;
		}
	}

	// On libère de la mémoire les polynômes qui ne servent plus
	polynomial_free(z1);
	polynomial_free(z0);

	// Et on retourne le résultat
	return z2;
}

polynomial_t *polynomial_pow(polynomial_t *p, long n)
{
	polynomial_t *q = NULL, *tmp = NULL;
	unsigned long degree = labs(n);
	char str[4096] = { 0 };

	sprintf(str, "%ld", n);

	if (p == NULL)
		return NULL;
	else if (degree == 0)
	{
		q = polynomial_init(NULL);
		if (q == NULL)
			return NULL;

		q->name = (char*) malloc((sizeof(p->name) + strlen(str) + 1) * sizeof(char));
		if (q->name == NULL)
		{
			free(q);

			return NULL;
		}

		strcpy(q->name, p->name);
		strcat(q->name, "^");
		strcat(q->name, str);

		polynomial_append(q, complex_init(1.0, 0.0), 0);

		return q;
	}

	if (degree % 2 == 0)
	{
		q = polynomial_pow(p, degree / 2);
		if (q == NULL)
			return NULL;

		tmp = polynomial_pow(q, 2);
		if (tmp == NULL)
		{
			polynomial_free(q);

			return NULL;
		}

		polynomial_free(q);
		q = tmp;

		if (q->name != NULL)
			free(q->name);

		q->name = (char*) malloc((sizeof(p->name) + strlen(str) + 1) * sizeof(char));
		if (q->name == NULL)
		{
			polynomial_free(q);

			return NULL;
		}

		strcpy(q->name, p->name);
		strcat(q->name, "^");
		strcat(q->name, str);
	}
	else
	{
		q = polynomial_pow(p, degree - 1);
		if (q == NULL)
			return NULL;

		tmp = polynomial_prod(p, q, NULL);
		if (tmp == NULL)
		{
			polynomial_free(q);

			return NULL;
		}

		polynomial_free(q);
		q = tmp;

		if (q->name != NULL)
			free(q->name);

		q->name = (char*) malloc((sizeof(p->name) + strlen(str) + 1) * sizeof(char));
		if (q->name == NULL)
		{
			polynomial_free(q);

			return NULL;
		}

		strcpy(q->name, p->name);
		strcat(q->name, "^");
		strcat(q->name, str);
	}

	// Inversion et division non géré pour le moment
	if (n < 0)
	{
		polynomial_free(q);

		return NULL;
	}

	return q;
}
