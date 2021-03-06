#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <type/polynomial.h>

polynomial_t *polynomial_init(const char *name)
{
	polynomial_t *p = (polynomial_t*) malloc(sizeof(polynomial_t));
	if (p == NULL)
		return NULL;

	// Si on a fourni un nom au polyn�me, on le copie
	if (name != NULL)
	{
		p->name = (char*) malloc(sizeof(name) * sizeof(char));
		if (p->name != NULL)
			strcpy(p->name, name);
	}
	else
		p->name = NULL;

	// On initialise les autres champs
	p->degree = 0;
	p->size = 0;
	p->pow = 1;
	p->first = NULL;
	p->last = NULL;
	p->previous = NULL;
	p->next = NULL;

	// Et on retourne l'adresse
	return p;
}

void polynomial_free(polynomial_t *p)
{
	monomial_t *m = NULL, *tmp = NULL;

	// Petite mesure de s�curit�
	if (p == NULL)
		return;

	// On lib�re de la m�moire tous les mon�mes du polyn�me
	m = p->first;
	while (m != NULL)
	{
		tmp = m->next;

		monomial_free(m);

		m = tmp;
	}

	// Et on lib�re le reste de la m�moire
	free(p->name);
	free(p);
}

void polynomial_display(polynomial_t *p)
{
	monomial_t *iterator = NULL;

	if (p == NULL)
		return;

	if (p->name != NULL)
		fprintf(stdout, "%s(X) = ", p->name);

	for (iterator = p->first ; iterator != NULL ; iterator = iterator->next)
	{
		monomial_display(iterator);

		if (iterator->next != NULL)
        {
            if (iterator->coef->re == 0 && iterator->coef->im == 0);
            else
                printf(" + ");
        }
	}
}

complex_t *polynomial_eval(polynomial_t *p, complex_t *coef, monomial_t *m, complex_t *eval)
{
	complex_t *result = NULL, *tmp = NULL;
	unsigned long diff = 0;

	if (p == NULL || coef == NULL || eval == NULL)
		return NULL;

	if (p->first->degree == 0)
		return complex_init(coef->re, coef->im);
	else
	{
		diff = (m == NULL) ? p->last->degree : m->previous->degree - m->degree;
		while (diff > 0)
		{
			if (result == NULL)
			{
				result = complex_prod(coef, eval);
				if (result == NULL)
					return NULL;
			}
			else
			{
				tmp = complex_prod(result, eval);
				if (tmp == NULL)
				{
					complex_free(result);

					return NULL;
				}

				complex_free(result);
				result = tmp;
			}

			diff--;
		}

		if (m != NULL)
		{
			tmp = complex_sum(result, m->coef);
			if (tmp == NULL)
			{
				complex_free(result);

				return NULL;
			}

			complex_free(result);
			result = tmp;

			if (m->next != NULL || m->degree > 0)
			{
				result = polynomial_eval(p, tmp, m->next, eval);
				complex_free(tmp);
			}
		}

		return result;
	}
}

void polynomial_reduce(polynomial_t *p, unsigned long n)
{
	monomial_t *iterator = NULL;

	if (p == NULL || p->degree < n)
		return;

	for (iterator = p->first; iterator != NULL; iterator = iterator->next)
		iterator->degree -= n;

	p->degree = p->first->degree;
}


void polynomial_increase(polynomial_t *p, unsigned long n)
{
	monomial_t *iterator = NULL;

	if (p == NULL)
		return;

	for (iterator = p->first; iterator != NULL; iterator = iterator->next)
		iterator->degree += n;

	p->degree = p->first->degree;
}

void polynomial_insert(polynomial_t *p, monomial_t *m)
{
	monomial_t *current = NULL;
	complex_t *tmp = NULL;

	// Mesure de s�curit�
	if (p == NULL || m == NULL)
		return;

	// On parcourt la liste jusqu'� ce que la puissance de mon�me ne soit plus inf�rieure
	current = p->first;
	while (current != NULL && m->degree < current->degree)
		current = current->next;


	// S'il n'y a pas d'�l�ments dans la liste
	if (current == NULL && p->first == NULL && p->last == NULL)
	{
		// On d�finit le mon�me comme le premier et dernier �l�ment du polyn�me
		p->first = m;
		p->last = m;
		p->degree = m->degree;

		p->size++;
	}
	else if (current == NULL) // Si on se trouve � la fin du polyn�me
	{
		// On d�finit la nouvelle fin du polyn�me
		m->previous = p->last;
		m->previous->next = m;
		p->last = m;

		p->size++;
	}
	else if (current->degree == m->degree) // Si on est dans le polyn�me et que le mon�me courant � le m�me degr�
	{
		// On fait la somme des facteurs
		tmp = complex_sum(current->coef, m->coef);
		if (tmp == NULL)
			return;

		complex_free(current->coef);
		current->coef = tmp;

		// Si notre mon�me a un coefficient nul
		if (current->coef->mod == 0.0)
			polynomial_remove(p, current->degree);

		// Et on lib�re le mon�me � ins�rer pour n'en garder qu'un
		monomial_free(m);
	}
	else // Sinon
	{
		// On place le mon�me dans le polyn�me
		m->previous = current->previous;
		m->next = current;

		// On r�gle les liens ascendant et descendant du mon�me
		current->previous = m;
		if (m->previous != NULL)
			m->previous->next = m;
		else
			p->first = m;

		// Si le mon�me ins�r� a le plus grand degr�
		if (m->degree > p->degree)
			p->degree = m->degree;

		p->size++;
	}
}

void polynomial_append(polynomial_t *p, complex_t *coef, unsigned long degree)
{
	monomial_t *m = NULL;

	// Mesure de s�curit�
	if (p == NULL || coef == NULL)
		return;

	if (coef->re == 0.0 && coef->im == 0.0)
	{
		complex_free(coef);

		return;
	}

	// On alloue en m�moire le mon�me � ajouter
	m = monomial_init(coef, degree);
	if (m == NULL)
		return;

	// Et on l'ins�re dans le polyn�me
	polynomial_insert(p, m);
}

polynomial_t *polynomial_extract(polynomial_t *p, unsigned long degree, unsigned long end)
{
	polynomial_t *q = NULL;
	complex_t *z = NULL;
	monomial_t *iterator = NULL;
	unsigned long i = 0;

	if (p == NULL)
		return NULL;

	q = polynomial_init(NULL);
	if (q == NULL)
		return NULL;

	for (i = p->degree, iterator = p->first; i >= end && iterator != NULL; i--, iterator = iterator->next)
	{
		if (degree >= iterator->degree && iterator->degree >= end)
		{
			z = complex_init(iterator->coef->re, iterator->coef->im);
			if (z == NULL)
			{
				polynomial_free(q);

				return NULL;
			}

			polynomial_append(q, z, iterator->degree);
		}
	}

	if (q->size == 0)
	{
		polynomial_free(q);
		q = NULL;
	}

	return q;
}

polynomial_t *polynomial_extractReal(polynomial_t *p)
{
	polynomial_t *q = NULL;
	monomial_t *iterator = NULL;
	char *name = NULL;

	if (p == NULL)
		return NULL;

	q = polynomial_init(NULL);
	if (q == NULL)
		return NULL;

	name = (char*) malloc((sizeof(p->name) + 3) * sizeof(char));
	if (name != NULL)
	{
		strcpy(name, "Re_");
		strcat(name, p->name);
		
		q->name = name;
	}

	for (iterator = p->first ; iterator != NULL ; iterator = iterator->next)
		polynomial_append(q, complex_init(iterator->coef->re, 0.0), iterator->degree);

	return q;
}

polynomial_t *polynomial_extractImaginary(polynomial_t *p)
{
	polynomial_t *q = NULL;
	monomial_t *iterator = NULL;
	char *name = NULL;

	if (p == NULL)
		return NULL;

	q = polynomial_init(NULL);
	if (q == NULL)
		return NULL;

	name = (char*) malloc((sizeof(p->name) + 3) * sizeof(char));
	if (name != NULL)
	{
		strcpy(name, "Im_");
		strcat(name, p->name);

		q->name = name;
	}

	for (iterator = p->first; iterator != NULL; iterator = iterator->next)
		polynomial_append(q, complex_init(0.0, iterator->coef->im), iterator->degree);

	return q;
}

void polynomial_remove(polynomial_t *p, unsigned long degree)
{
	monomial_t *current = NULL, *tmp = NULL;

	// Mesure de s�curit�
	if (p == NULL)
		return;

	// On parcourt le polyn�me jusqu'au mon�me � supprimer
	current = p->first;
	while (current != NULL && current->degree != degree)
		current = current->next;

	// Si on n'a pas trouv� le mon�me, on arr�te
	if (current == NULL)
		return;

	// On retire le mon�me du polyn�me
	if (current->previous != NULL)
		current->previous->next = current->next;
	else
		p->first = current->next;

	if (current->next != NULL)
		current->next->previous = current->previous;
	else
		p->last = current->previous;

	// Si c'�tait le mon�me de plus grand degr�
	if (p->degree == current->degree)
	{
		// On doit retrouver le nouveau degr� du polyn�me (par d�faut, il vaut 0)
		tmp = p->first;
		p->degree = 0;

		while (tmp != NULL)
		{
			if (tmp != current && tmp->degree > p->degree)
				p->degree = tmp->degree;
		}
	}

	// On lib�re le mon�me de la m�moire et on d�cr�mente la taille du polyn�me
	monomial_free(current);
	p->size--;
}
