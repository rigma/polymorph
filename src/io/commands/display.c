#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <type/polynomial.h>
#include <type/polymorph.h>
#include <io/commands.h>
#include <utils.h>

int display(entry_t *list, char *args)
{
	char **table = NULL;
	entry_t *p = NULL;
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

	p = entry_get(list, table[1]);
	if (p != NULL)
	{
		if (p->type == POLYNOMIAL)
			polynomial_display((polynomial_t*)p->polynomial);
		/*else if (p->type == POLYMORPH)
			polymorph_display((polymorph_t*) p->polynomial); */
	}

	fprintf(stdout, "\n");

	for (i = 0; i < size; i++)
		free(table[i]);

	free(table);

	return EXIT_SUCCESS;
}
