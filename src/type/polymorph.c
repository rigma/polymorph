#include <stdlib.h>
#include <string.h>

#include <type/polymorph.h>

polymorph_t *polymorph_init(const char *name)
{
	polymorph_t *p = NULL;

	// Le polynôme doit avoir un nom
	if (name == NULL)
		return NULL;

	// On tente d'allouer en mémoire la structure
	p = (polymorph_t*) malloc(sizeof(polymorph_t));
	if (p == NULL)
		return NULL; // Si ça échoue, on renvoit NULL

	// On "copie" le nom du polynôme dans la structure
	p->name = (char*) malloc(sizeof(name) * sizeof(char));
	if (p->name == NULL)
	{
		// Si on ne peut pas allouer, on libère la structure de la mémoire
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

	// Mesure de sécurité
	if (p == NULL)
		return;

	// On va d'abord libérer tous les polynômes qui compose le polynôme factorisé
	root = p->first;
	while (root != NULL)
	{
		tmp = root->next;

		polynomial_free(root);

		root = tmp;
	}

	// Puis on libère le nom de la structure et elle-même
	free(p->name);
	free(p);
}

void polymorph_append(polymorph_t *p, complex_t *root)
{
	polynomial_t *element = NULL;

	// Mesure de sécurité
	if (p == NULL || root == NULL)
		return;

	// On parcours d'abord le polynôme pour savoir si la racine est déjà présente
	element = p->first;
	while (element != NULL && !complex_compare(root, element->last->coef))
		element = element->next;

	// Si la racine n'est pas déjà présente dans le polynôme
	if (element == NULL)
	{
		// On alloue en mémoire le nouveau polynôme
		element = (polynomial_t *) polynomial_init(NULL);
		if (element == NULL)
			return;

		// On ajoute les monômes correspondants à la racine
		polynomial_append(element, complex_init(1.0, 0.0), 1);
		polynomial_append(element, complex_scalarProd(-1.0, root), 0);

		// Puis on l'insère dans le polynôme factorisé
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
	else // Sinon, on incrémente le compteur de racine multiple
		element->pow++;

	// Enfin, on incrémente la taille du polynôme factorisé
	p->size++;
}

void polymorph_remove(polymorph_t *p, complex_t *root)
{
	polynomial_t *element = NULL;

	// Mesure de sécurité
	if (p == NULL || element == NULL)
		return;

	// On parcours la liste jusqu'à l'élément désiré
	element = p->first;
	while (element != NULL && !complex_compare(root, element->last->coef))
		element = element->next;

	// S'il n'est pas présent, on s'arrête
	if (element == NULL)
		return;

	// On le retire du polynôme
	if (element->previous != NULL)
		element->previous->next = element->next;
	else
		p->first = element->next;

	if (element->next != NULL)
		element->next->previous = element->previous;
	else
		p->last = element->previous;

	// On libère l'élément de la mémoire et on décrémente la taille
	polynomial_free(element);
	p->size--;

	// Au cas où
	if (p->size == 0)
	{
		p->first = NULL;
		p->last = NULL;
	}
}
