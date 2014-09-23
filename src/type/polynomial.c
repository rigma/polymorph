#include <stdlib.h>
#include <string.h>

#include <type/polynomial.h>

polynomial_t *polynomial_init(const char *name)
{
	polynomial_t *p = (polynomial_t*) malloc(sizeof(polynomial_t));
	if (p == NULL)
		return NULL;

	// Si on a fourni un nom au polynôme, on le copie
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

	// Petite mesure de sécurité
	if (p == NULL)
		return;

	// On libère de la mémoire tous les monômes du polynôme
	m = p->first;
	while (m != NULL)
	{
		tmp = m->next;

		monomial_free(m);

		m = tmp;
	}

	// Et on libère le reste de la mémoire
	free(p->name);
	free(p);
}

void polynomial_append(polynomial_t *p, complex_t *coef, unsigned long degree)
{
	monomial_t *m = NULL;

	// Mesure de sécurité
	if (p == NULL || coef == NULL)
		return;

	// On alloue en mémoire le monôme à ajouter
	m = monomial_init(coef, degree);
	if (m == NULL)
		return;

	// Et on l'insère dans le polynôme
	polynomial_insert(p, m);
}

void polynomial_insert(polynomial_t *p, monomial_t *m)
{
	monomial_t *current = NULL;
	complex_t *tmp = NULL;

	// Mesure de sécurité
	if (p == NULL || m == NULL)
		return;

	// On parcourt la liste jusqu'à ce que la puissance de monôme ne soit plus inférieure
	current = p->first;
	while (current != NULL && m->degree < current->degree)
		current = current->next;

	
	// S'il n'y a pas d'éléments dans la liste
	if (current == NULL && p->first == NULL && p->last == NULL)
	{
		// On définit le monôme comme le premier et dernier élément du polynôme
		p->first = m;
		p->last = m;
		p->degree = m->degree;
	}
	else if (current == NULL) // Si on se trouve à la fin du polynôme
	{
		// On définit la nouvelle fin du polynôme
		m->previous = p->last;
		m->previous->next = m;
		p->last = m;
	}
	else if (current->degree == m->degree) // Si on est dans le polynôme et que le monôme courant à le même degré
	{
		// On fait la somme des facteurs
		tmp = complex_sum(current->coef, m->coef);
		if (tmp == NULL)
			return;

		complex_free(current->coef);
		current->coef = tmp;
		
		// Et on libère le monôme à insérer pour n'en garder qu'un
		monomial_free(m);
	}
	else // Sinon
	{
		// On place le monôme dans le polynôme
		m->previous = current->previous;
		m->next = current;

		// On règle les liens ascendant et descendant du monôme
		current->previous = m;
		if (m->previous != NULL)
			m->previous->next = m;
		else
			p->first = m;

		// Si le monôme inséré a le plus grand degré
		if (m->degree > p->degree)
			p->degree = m->degree;
	}

	p->size++;
}

void polynomial_remove(polynomial_t *p, unsigned long degree)
{
	monomial_t *current = NULL, *tmp = NULL;

	// Mesure de sécurité
	if (p == NULL)
		return;

	// On parcourt le polynôme jusqu'au monôme à supprimer
	current = p->first;
	while (current != NULL && current->degree != degree)
		current = current->next;

	// Si on n'a pas trouvé le monôme, on arrête
	if (current == NULL)
		return;

	// On retire le monôme du polynôme
	if (current->previous != NULL)
		current->previous->next = current->next;
	else
		p->first = current->next;

	if (current->next != NULL)
		current->next->previous = current->previous;
	else
		p->last = current->previous;

	// Si c'était le monôme de plus grand degré
	if (p->degree == current->degree)
	{
		// On doit retrouver le nouveau degré du polynôme (par défaut, il vaut 0)
		tmp = p->first;
		p->degree = 0;

		while (tmp != NULL)
		{
			if (tmp != current && tmp->degree > p->degree)
				p->degree = tmp->degree;
		}
	}

	// On libère le monôme de la mémoire et on décrémente la taille du polynôme
	monomial_free(current);
	p->size--;
}
