#include <stdlib.h>

#include <type/polynomial_table.h>
#include <type/polynomial.h>
#include <type/polymorph.h>

polynomial_table_t *polynomial_table_init(unsigned long size)
{
	polynomial_table_t *table = NULL;
	unsigned long i = 0;
	
	table = (polynomial_table_t*) malloc(sizeof(polynomial_table_t));
	if (table == NULL)
		return NULL;

	table->size = size;
	table->realSize = size * 5 / 4 + 1;

	do
	{
		table->polynomials = (polynomial_table_entry_t**) malloc(table->realSize * sizeof(polynomial_table_entry_t*));
		i++;
	} while (table->polynomials == NULL && i < 128);

	if (i == 128)
	{
		free(table);

		return NULL;
	}

	for (i = 0 ; i < table->realSize ; i++)
		table->polynomials[i] = NULL;

	return table;
}

void polynomial_table_free(polynomial_table_t *table)
{
	unsigned long i = 0;

	if (table == NULL)
		return;

	for (i = 0 ; i < table->realSize ; i++)
	{
		if (table->polynomials[i] != NULL)
		{
			if (table->polynomials[i]->type == POLYNOMIAL)
				polynomial_free((polynomial_t*) table->polynomials[i]->polynomial);
			else if (table->polynomials[i]->type == POLYMORPH)
				polymorph_free((polymorph_t*) table->polynomials[i]->polynomial);

			free(table->polynomials[i]);
		}
	}

	free(table);
}

unsigned long polynomial_table_hash(polynomial_table_t *table, const char *str)
{
	unsigned int r1 = 0, r2 = 0;
	unsigned int subchunk = 0;
	unsigned long chunk = 0;

	while (*str)
	{
		subchunk = *str | *(str + 1) << 8;
		chunk = subchunk | subchunk << 16;

		r1 = r1 ^ chunk >> (r2 & 0xf);
		r2 = r2 ^ chunk >> (r1 & 0xf);

		if (!*(str + 1))
			break;
		
		str += 2;
	}

	return (r1 ^ r2) % table->realSize;
}

polynomial_table_entry_t *polynomial_table_get(polynomial_table_t *table, unsigned long hash)
{
	return (table == NULL) ? NULL : table->polynomials[hash];
}

char polynomial_table_append(polynomial_table_t *table, void *polynomial, unsigned char type)
{
	unsigned long hash = 0;

	if (table == NULL || polynomial == NULL)
		return 0;

	if (type == POLYNOMIAL)
		hash = polynomial_table_hash(table, ((polynomial_t*) polynomial)->name);
	else if (type == POLYMORPH)
		hash = polynomial_table_hash(table, ((polymorph_t*) polynomial)->name);
	else
		return 0;

	if (table->polynomials[hash] != NULL)
		return 0;
	
	table->polynomials[hash] = (polynomial_table_entry_t*) malloc(sizeof(polynomial_table_entry_t));
	if (table->polynomials[hash] == NULL)
		return 0;

	table->polynomials[hash]->polynomial = polynomial;
	table->polynomials[hash]->type = type;

	return 1;
}

char polynomial_table_remove(polynomial_table_t *table, const char *name)
{
	unsigned long hash = 0;

	if (table == NULL || name == NULL)
		return 0;

	hash = polynomial_table_hash(table, name);

	if (table->polynomials[hash] == NULL)
		return 0;

	if (table->polynomials[hash]->type == POLYNOMIAL)
		polynomial_free((polynomial_t*) table->polynomials[hash]->polynomial);
	else if (table->polynomials[hash]->type == POLYMORPH)
		polymorph_free((polymorph_t*) table->polynomials[hash]->polynomial);
	else
		free(table->polynomials[hash]->polynomial);

	free(table->polynomials[hash]);
	table->polynomials[hash] = NULL;

	return 1;
}
