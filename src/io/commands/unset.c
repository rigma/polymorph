#include <stdlib.h>
#include <stdio.h>

#include <type/polynomial.h>
#include <io/commands.h>
#include <utils.h>

int unset(entry_t **list, char *args)
{
	char **table = NULL;
	size_t size = 0, i = 0;

	if (list == NULL || args == NULL)
		return EXIT_FAILURE;

	table = split(args, ' ', &size);
	if (table == NULL || size == 1)
	{
		if (table != NULL)
		{
			free(*table);
			free(table);
		}

		return EXIT_FAILURE;
	}

	entry_remove(list, table[1]);

	for (i = 0; i < size; i++)
		free(table[i]);

	free(table);

	return EXIT_SUCCESS;
}
