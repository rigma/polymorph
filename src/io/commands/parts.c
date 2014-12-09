#include <stdlib.h>
#include <stdio.h>

#include <type/polynomial.h>
#include <io/commands.h>
#include <utils.h>

int re(entry_t **list, char *args)
{
	entry_t *e = NULL;
	polynomial_t *re = NULL;
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

	e = entry_get(*list, table[1]);
	if (e == NULL || e->type != POLYNOMIAL)
	{
		for (i = 0; i < size; i++)
			free(table[i]);

		free(table);

		return EXIT_FAILURE;
	}

	re = polynomial_extractReal((polynomial_t*) e->polynomial);
	if (re == NULL)
	{
		for (i = 0; i < size; i++)
			free(table[i]);

		free(table);

		return EXIT_FAILURE;
	}

	if (re->size > 0)
	{
		polynomial_display(re);
		fprintf(stdout, "\n");

		entry_add(list, (void*) re, POLYNOMIAL);
	}
	else
		polynomial_free(re);

	for (i = 0; i < size; i++)
		free(table[i]);

	free(table);

	return EXIT_SUCCESS;
}

int im(entry_t **list, char *args)
{
	entry_t *e = NULL;
	polynomial_t *im = NULL;
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

	e = entry_get(*list, table[1]);
	if (e == NULL || e->type != POLYNOMIAL)
	{
		for (i = 0; i < size; i++)
			free(table[i]);

		free(table);

		return EXIT_FAILURE;
	}

	im = polynomial_extractImaginary((polynomial_t*) e->polynomial);
	if (im == NULL)
	{
		for (i = 0; i < size; i++)
			free(table[i]);

		free(table);

		return EXIT_FAILURE;
	}

	if (im->size > 0)
	{
		polynomial_display(im);
		fprintf(stdout, "\n");

		entry_add(list, (void*) im, POLYNOMIAL);
	}
	else
		polynomial_free(im);

	for (i = 0; i < size; i++)
		free(table[i]);

	free(table);

	return EXIT_SUCCESS;
}
