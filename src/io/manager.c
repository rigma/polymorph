#include <stdlib.h>
#include <string.h>

#include <io/manager.h>

void entry_free(entry_t **list)
{
	entry_t *next = NULL;

	if (*list == NULL)
		return;

	while (*list != NULL)
	{
		next = (*list)->next;

		if ((*list)->type == POLYNOMIAL)
			polynomial_free((polynomial_t*) (*list)->polynomial);
		else if ((*list)->type == POLYMORPH)
			polymorph_free((polymorph_t*) (*list)->polynomial);
		else
			free((*list)->polynomial);

		free(*list);
		*list = next;
	}
}

void entry_add(entry_t **list, void *polynomial, unsigned char type)
{
	entry_t *iterator = NULL, *previous = NULL;

	if (polynomial == NULL)
		return;

	if (*list == NULL)
	{
		*list = (entry_t*) malloc(sizeof(entry_t));
		if (*list == NULL)
			return;

		(*list)->polynomial = polynomial;
		(*list)->type = type;
		(*list)->next = NULL;
	}
	else
	{
		previous = NULL;
		iterator = *list;
		while (iterator != NULL)
		{
			if (type == POLYNOMIAL && !strcmp(((polynomial_t*) iterator->polynomial)->name, ((polynomial_t*) polynomial)->name))
				break;
			else if (type == POLYMORPH && !strcmp(((polymorph_t*) iterator->polynomial)->name, ((polymorph_t*) polynomial)->name))
				break;

			previous = iterator;
			iterator = iterator->next;
		}
		
		if (iterator != NULL)
		{
			if (iterator->type == POLYNOMIAL)
				polynomial_free((polynomial_t*) iterator->polynomial);
			else if (iterator->type == POLYMORPH)
				polymorph_free((polymorph_t*) iterator->polynomial);

			iterator->polynomial = polynomial;
		}
		else
		{
			previous->next = (entry_t*) malloc(sizeof(entry_t));
			if (previous->next == NULL)
				return;

			previous->next->polynomial = polynomial;
			previous->next->type = type;
			previous->next->next = NULL;
		}
	}
}

void entry_remove(entry_t **list, char *name)
{
	entry_t *previous = NULL, *iterator = NULL;

	if (name == NULL)
		return;

	iterator = *list;
	while (iterator != NULL)
	{
		if (iterator->type == POLYNOMIAL && !strcmp(name, ((polynomial_t*) iterator->polynomial)->name))
			break;
		else if (iterator->type == POLYMORPH && !strcmp(name, ((polymorph_t*) iterator->polynomial)->name))
			break;

		previous = iterator;
		iterator = iterator->next;
	}

	if (previous == NULL)
		*list = iterator->next;
	else
		previous->next = iterator->next;

	if (iterator->type == POLYNOMIAL)
		polynomial_free((polynomial_t*) iterator->polynomial);
	else if (iterator->type == POLYMORPH)
		polymorph_free((polymorph_t*) iterator->polynomial);
	else
		free(iterator->polynomial);

	free(iterator);
}

entry_t *entry_get(entry_t *list, char *name)
{
	while (list != NULL)
	{
		if (list->type == POLYNOMIAL && !strcmp(name, ((polynomial_t*) list->polynomial)->name))
			return list;
		else if (list->type == POLYMORPH && !strcmp(name, ((polymorph_t*) list->polynomial)->name))
			return list;

		list = list->next;
	}

	return NULL;
}
