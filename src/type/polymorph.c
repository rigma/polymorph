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
