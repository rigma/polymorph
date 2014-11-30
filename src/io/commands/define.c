#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <type/polynomial.h>
#include <io/commands.h>

int define(buffer_t *buffer, entry_t **list, const char *name)
{
	polynomial_t *p = NULL;
	complex_t *z = NULL;
	char *output = NULL, *input = NULL;
	char run = 1;

	if (buffer == NULL)
		return EXIT_FAILURE;

	if (name == NULL)
	{
		buffer_read(buffer, 0, "Entrez le nom de v�tre polyn�me : ");
		name = buffer_get(buffer);
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
				printf("%s(X) = %s X ^ ", p->name, output);
			else
			{
				polynomial_display(p);
				printf(" + %s X ^ ", output);
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
