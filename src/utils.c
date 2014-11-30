#include <stdlib.h>
#include <string.h>

char **split(const char *str, char delemiter, size_t *size)
{
	char **table = NULL;
	void *tmp = NULL;
	size_t lenght = 0, i = 0;

	if (str == NULL || size == NULL)
		return NULL;

	*size = 1;

	table = (char**) malloc(sizeof(char*));
	if (table == NULL)
		return NULL;

	while (*str != '\0')
	{
		if (*str != delemiter)
		{
			lenght++;

			if (lenght == 1)
			{
				table[*size - 1] = (char*) malloc(sizeof(char));
				if (table[*size - 1] == NULL)
				{
					free(table);

					return NULL;
				}
			}
			else
			{
				tmp = realloc(table[*size - 1], lenght * sizeof(char));
				if (tmp == NULL)
				{
					for (i = 0 ; i < *size ; i++)
						free(table[i]);

					free(table);

					return NULL;
				}

				table[*size - 1] = (char*) tmp;
			}

			table[*size - 1][lenght - 1] = *str;
		}
		else
		{
			// On affecte le dernier caractère de la précédente chaîne
			lenght++;
			tmp = realloc(table[*size - 1], lenght * sizeof(char));
			if (tmp == NULL)
			{
				for (i = 0 ; i < *size ; i++)
					free(table[i]);

				free(table);

				return NULL;
			}

			table[*size - 1] = (char*) tmp;
			table[*size - 1][lenght - 1] = '\0';

			(*size)++;

			tmp = realloc(table, *size * sizeof(char*));
			if (tmp == NULL)
			{
				for (i = 0 ; i < *size - 1 ; i++)
					free(table[i]);

				free(table);

				return NULL;
			}

			table = (char**) tmp;
			lenght = 0;
		}

		str = str + 1;
	}

	// On referme la dernière chaîne de caractères
	lenght++;
	tmp = realloc(table[*size - 1], lenght * sizeof(char));
	if (tmp == NULL)
	{
		for (i = 0 ; i < *size ; i++)
			free(table[i]);

		free(table);

		return NULL;
	}

	table[*size - 1] = (char*) tmp;
	table[*size - 1][lenght - 1] = '\0';

	return table;
}