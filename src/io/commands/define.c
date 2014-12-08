#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <type/polynomial.h>
#include <io/commands.h>
#include <utils.h>

int define(buffer_t *buffer, entry_t **list, char *args)
{
	polynomial_t *p = NULL;
	complex_t *z = NULL;
	char **table = NULL, *output = NULL, *input = NULL, *name = NULL;
	char run = 1;
	size_t size = 0, i = 0;

	if (buffer == NULL)
		return EXIT_FAILURE;

	if (args == NULL)
	{
		buffer_read(buffer, 0, "Entrez le nom de vôtre polynôme : ");
		name = buffer_get(buffer);
	}
	else
	{
		table = split(args, ' ', &size);

		name = (char*) malloc(sizeof(table[1]) * sizeof(char));
		strcpy(name, table[1]);

		for (i = 0; i < size; i++)
			free(table[i]);

		free(table);
	}

	p = polynomial_init(name);
	if (p == NULL)
		return EXIT_FAILURE;

	while (run)
	{
		if (p->size == 0)
			printf("%s(X) = ", p->name);
		else
		{
			polynomial_display(p);
			printf(" + ");
		}

		buffer_read(buffer, 0, NULL);
		input = buffer_get(buffer);

		z = complex_fromString(input);

		if (z != NULL)
		{
			output = complex_toString(z, 0);

			if (p->size == 0)
			{
				if (z->re != 0.0 && z->im != 0.0)
					printf("%s(X) = (%s) X ^ ", p->name, output);
				else
					printf("%s(X) = %s X ^ ", p->name, output);
			}
			else
			{
				polynomial_display(p);

				if (z->re != 0.0 && z->im != 0.0)
					printf(" + (%s) X ^ ", output);
				else
					printf(" + (%s) X ^ ", output);
			}

			free(output);

			buffer_read(buffer, 0, NULL);
			input = buffer_get(buffer);

			polynomial_append(p, z, strtoul(input, NULL, 0));
			free(input);

			buffer_read(buffer, 0, "Voulez-vous continuer (oui/non) ? ");
			input = buffer_get(buffer);

			if (!strcmp(input, "non") || !strcmp(input, "n") || !strcmp(input, "N"))
				run = 0;
		}
	}

	entry_add(list, (void*) p, POLYNOMIAL);

	return EXIT_SUCCESS;
}
