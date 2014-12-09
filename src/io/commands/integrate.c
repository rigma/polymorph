#include <stdlib.h>
#include <stdio.h>

#include <type/polynomial.h>
#include <io/commands.h>
#include <analysis.h>
#include <utils.h>

int integrate(entry_t **list, char *args)
{
	complex_t *z = NULL;
	entry_t *e = NULL;
	polynomial_t *p = NULL, *q = NULL;
	size_t size = 0, i = 0;
	char **table = NULL, *c = NULL, count = 0;

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

	e = entry_get(*list, table[1]);
	if (e == NULL || e->type != POLYNOMIAL)
	{
		for (i = 0; i < size; i++)
			free(table[i]);

		free(table);

		return EXIT_FAILURE;
	}

	if (size > 2)
	{
		c = args;
		while (count < 2)
		{
			if (*c == ' ')
				count++;

			c++;
		}

		z = complex_fromString(c);
		if (z == NULL)
		{
			for (i = 0; i < size; i++)
				free(table[i]);

			free(table);

			return EXIT_FAILURE;
		}

		q = polynomial_integrate((polynomial_t*) e->polynomial, z);
	}
	else
		q = polynomial_integrate((polynomial_t*) e->polynomial, NULL);

	if (q == NULL)
	{
		if (z != NULL)
			complex_free(z);

		for (i = 0; i < size; i++)
			free(table[i]);

		free(table);

		return EXIT_FAILURE;
	}

	polynomial_display(q);
	fprintf(stdout, "\n");

	entry_add(list, (void*) q, POLYNOMIAL);

	for (i = 0; i < size; i++)
		free(table[i]);

	free(table);

	return EXIT_SUCCESS;
}
