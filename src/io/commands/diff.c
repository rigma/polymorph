#include <stdlib.h>
#include <stdio.h>

#include <type/polynomial.h>
#include <io/commands.h>
#include <analysis.h>
#include <utils.h>

int diff(entry_t **list, char *args)
{
	char **table = NULL;
	entry_t *e = NULL;
	polynomial_t *p = NULL, *q = NULL;
	size_t size = 0, i = 0;

	if (list == NULL || args == NULL)
		return EXIT_FAILURE;

	table = split(args, ' ', &size);
	if (table == NULL || size == 1)
	{
		if (table != NULL)
		{
			for (i = 0; i < size; i++)
				free(table[i]);

			free(table);
		}

		return EXIT_FAILURE;
	}

	e = entry_get(*list, table[1]);
	if (e == NULL || e->type != POLYNOMIAL)
	{
		for (i = 0; i < size; i++)
			free(table[i]);

		free(table);

		return EXIT_FAILURE;
	}

	p = (polynomial_t*) e->polynomial;
	q = polynomial_differentiate(p);

	polynomial_display(q);
	printf("\n");

	entry_add(list, (void*) q, POLYNOMIAL);

	for (i = 0; i < size; i++)
		free(table[i]);

	free(table);

	return EXIT_SUCCESS;
}
