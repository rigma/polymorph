#include <stdlib.h>
#include <string.h>

#include <type/polymorph.h>

polymorph_t *polymorph_init(const char *name)
{
	polymorph_t *p = NULL;

	// Le polyn�me doit avoir un nom
	if (name == NULL)
		return NULL;

	// On tente d'allouer en m�moire la structure
	p = (polymorph_t*) malloc(sizeof(polymorph_t));
	if (p == NULL)
		return NULL; // Si �a �choue, on renvoit NULL

	// On "copie" le nom du polyn�me dans la structure
	p->name = (char*) malloc(sizeof(name) * sizeof(char));
	if (p->name == NULL)
	{
		// Si on ne peut pas allouer, on lib�re la structure de la m�moire
		// et on retourne NULL.
		free(p);

		return NULL;
	}

	strcpy(p->name, name);

	// On initialise les autres champs de la structure
	p->size = 0;
	p->first = NULL;
	p->last = NULL;

	// Et on retourne l'adresse
	return p;
}

void polymorph_free(polymorph_t *p)
{
	polynomial_t *root = NULL, *tmp = NULL;

	// Mesure de s�curit�
	if (p == NULL)
		return;

	// On va d'abord lib�rer tous les polyn�mes qui compose le polyn�me factoris�
	root = p->first;
	while (root != NULL)
	{
		tmp = root->next;

		polynomial_free(root);

		root = tmp;
	}

	// Puis on lib�re le nom de la structure et elle-m�me
	free(p->name);
	free(p);
}

void polymorph_append(polymorph_t *p, complex_t *root)
{
	polynomial_t *element = NULL;

	// Mesure de s�curit�
	if (p == NULL || root == NULL)
		return;

	// On parcours d'abord le polyn�me pour savoir si la racine est d�j� pr�sente
	element = p->first;
	while (element != NULL && !complex_compare(root, element->last->coef))
		element = element->next;

	// Si la racine n'est pas d�j� pr�sente dans le polyn�me
	if (element == NULL)
	{
		// On alloue en m�moire le nouveau polyn�me
		element = (polynomial_t *) polynomial_init(NULL);
		if (element == NULL)
			return;

		// On ajoute les mon�mes correspondants � la racine
		polynomial_append(element, complex_init(1.0, 0.0), 1);
		polynomial_append(element, complex_scalarProd(-1.0, root), 0);

		// Puis on l'ins�re dans le polyn�me factoris�
		if (p->last == NULL)
		{
			p->first = element;
			p->last = element;
		}
		else
		{
			p->last->next = element;
			element->previous = p->last;
			p->last = element;
		}
	}
	else // Sinon, on incr�mente le compteur de racine multiple
		element->pow++;

	// Enfin, on incr�mente la taille du polyn�me factoris�
	p->size++;
}

void polymorph_remove(polymorph_t *p, complex_t *root)
{
	polynomial_t *element = NULL;

	// Mesure de s�curit�
	if (p == NULL || element == NULL)
		return;

	// On parcours la liste jusqu'� l'�l�ment d�sir�
	element = p->first;
	while (element != NULL && !complex_compare(root, element->last->coef))
		element = element->next;

	// S'il n'est pas pr�sent, on s'arr�te
	if (element == NULL)
		return;

	// On le retire du polyn�me
	if (element->previous != NULL)
		element->previous->next = element->next;
	else
		p->first = element->next;

	if (element->next != NULL)
		element->next->previous = element->previous;
	else
		p->last = element->previous;

	// On lib�re l'�l�ment de la m�moire et on d�cr�mente la taille
	polynomial_free(element);
	p->size--;

	// Au cas o�
	if (p->size == 0)
	{
		p->first = NULL;
		p->last = NULL;
	}
}
