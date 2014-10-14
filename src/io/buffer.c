#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <io/buffer.h>

buffer_t *buffer_init(size_t offset)
{
	buffer_t *b = (buffer_t*) malloc(sizeof(buffer_t));
	if (b == NULL)
		return (buffer_t*) NULL;

	if (offset > 0)
	{
		b->size = offset;
		b->buffer = (char**) malloc(offset * sizeof(char*));
	}
	else
	{
		b->size = 0;
		b->buffer = (char**) NULL;
	}

	return b;
}

void buffer_free(buffer_t *b)
{
	size_t i = 0;

	if (b == NULL)
		return;

	if (b->size > 0)
	{
		for (i = 0 ; i < b->size ; i++)
			free(b->buffer[i]);

		free(b->buffer);
	}

	free(b);
}

char buffer_read(buffer_t *b, size_t lenght, const char *prefix)
{
	char **buffer = NULL, *tmp = NULL;
	char c = 0;
	size_t size = 0, i = 0, j = 0;

	if (b == NULL)
		return 0;

	if (prefix != NULL)
		fputs(prefix, stdout);

	for (i = 0 ; i < b->size ; i++)
	{
		if (b->buffer[i] == NULL)
			tmp = b->buffer[i];
	}

	if (i == b->size)
	{
		size = b->size;
		b->size++;

		buffer = (char**) realloc(b->buffer, b->size * sizeof(char*));
		if (buffer == NULL)
		{
			b->size = size;

			return 0;
		}

		b->buffer = buffer;
	}

	if (lenght > 0)
	{
		b->buffer[i] = (char*) malloc((lenght + 1) * sizeof(char));
		if (b->buffer[i] == NULL)
			return 0;
		
		j = 0;
		do
		{
			c = fgetc(stdin);

			if (c != '\n' && c != '\0')
			{
				b->buffer[i][j] = c;
				j++;
			}
		} while (c != '\0' && c != '\n' && j < lenght);

		b->buffer[lenght] = '\0';
	}
	else
	{
		size = 0;
		j = 0;

		do
		{
			size++;

			if (size == 1)
				tmp = (char*) malloc(sizeof(char));
			else
				tmp = (char*) realloc(b->buffer[i], size * sizeof(char));

			if (tmp == NULL)
				return 0;

			tmp[size - 1] = 0;
			b->buffer[i] = tmp;
			c = fgetc(stdin);

			if (c != '\0' && c != '\n')
			{
				b->buffer[i][j] = c;
				j++;
			}
		} while (c != '\0' && c != '\n');

		size++;
		tmp = (char*) realloc(b->buffer[i], size * sizeof(char));
		if (tmp == NULL)
			return 0;

		b->buffer[i] = tmp;
		b->buffer[i][size - 1] = '\0';
	}

	return 1;
}

char *buffer_get(buffer_t *b)
{
	char **tmp = (char**) NULL, *str = (char*) NULL;
	size_t size = 0, i = 0;

	if (b == NULL)
		return (char*) NULL;

	if (b->size > 0)
	{
		str = *b->buffer;

		for (i = 0 ; i < b->size - 1 ; i++)
			b->buffer[i] = b->buffer[i + 1];

		size = b->size;
		b->size--;

		if (b->size > 0)
		{
			tmp = (char**) realloc(b->buffer, b->size * sizeof(char*));
			if (tmp == NULL)
			{
				b->size = size;
				b->buffer[b->size - 1] = str;

				return (char*) NULL;
			}

			b->buffer = tmp;
		}
		else
		{
			free(b->buffer);

			b->buffer = NULL;
		}
	}

	return str;
}
