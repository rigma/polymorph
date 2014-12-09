#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <type/polynomial.h>
#include <io/commands.h>
#include <utils.h>

int expr(entry_t **list, char *args)
{
	complex_t *z = NULL, *eval = NULL;
	entry_t *e = NULL;
	polynomial_t *p = NULL;
	char **table = NULL, *name = NULL, *number = NULL, *tmp = NULL, *equality = NULL, *c = NULL;
	size_t size = 0, lenght = 0, i = 0;

	if (list == NULL || args == NULL)
		return EXIT_FAILURE;

	table = split(args, ' ', &size);
	if (table == NULL)
		return EXIT_FAILURE;

	if (strchr(args, '(') != NULL && size <= 3)
	{
		lenght = 1;
		c = args;

		while (*c != '(')
		{
			if (lenght == 1)
				tmp = (char*) malloc(sizeof(char));
			else
				tmp = (char*) realloc(name, lenght * sizeof(char));

			if (tmp == NULL)
			{
				if (name != NULL)
					free(name);

				return EXIT_FAILURE;
			}

			name = tmp;
			name[lenght - 1] = *c;

			lenght++;
			c++;
		}

		tmp = (char*) realloc(name, lenght * sizeof(char));
		if (tmp == NULL)
		{
			free(name);

			return EXIT_FAILURE;
		}

		name = tmp;
		name[lenght - 1] = '\0';

		c++;
		lenght = 1;

		while (*c != ')')
		{
			if (lenght == 1)
				tmp = (char*) malloc(sizeof(char));
			else
				tmp = (char*) realloc(number, lenght * sizeof(char));

			if (tmp == NULL)
			{
				if (number != NULL)
					free(number);

				free(name);

				return EXIT_FAILURE;
			}

			number = tmp;
			number[lenght - 1] = *c;

			lenght++;
			c++;
		}

		tmp = (char*)realloc(number, lenght * sizeof(char));
		if (tmp == NULL)
		{
			free(number);
			free(name);

			return EXIT_FAILURE;
		}

		number = tmp;
		number[lenght - 1] = '\0';

		z = complex_fromString(number);
		if (z == NULL)
		{
			free(number);
			free(name);

			return EXIT_FAILURE;
		}

		free(number);
		number = NULL;

		e = entry_get(*list, name);
		if (e == NULL || e->type != POLYNOMIAL)
		{
			complex_free(z);

			free(name);

			return EXIT_FAILURE;
		}

		eval = polynomial_eval((polynomial_t*)e->polynomial, ((polynomial_t*)e->polynomial)->first->coef, ((polynomial_t*)e->polynomial)->first->next, z);
		if (eval == NULL)
		{
			complex_free(z);

			free(name);

			return EXIT_FAILURE;
		}

		number = complex_toString(eval, 0);
		if (number == NULL)
		{
			complex_free(eval);
			complex_free(z);

			free(name);

			return EXIT_FAILURE;
		}

		fprintf(stdout, "%s\n", number);

		complex_free(z);
		complex_free(eval);

		free(name);
		free(number);
	}
	/*else
	{
		equality = strchr(args, '=');
		c = equality + 1;
	}*/

	return EXIT_SUCCESS;
}
