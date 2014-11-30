#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#include <type/complex.h>
#include <utils.h>

complex_t *complex_init(double re, double im)
{
	complex_t *z = (complex_t*) malloc(sizeof(complex_t));
	if (z == NULL)
		return NULL;

	// Stockage de la partie réelle et de la partie imaginaire du complexe
	// et calcul de son module
	z->re = re;
	z->im = im;
	z->mod = sqrt(re * re + im * im);

	return z;
}

void complex_free(complex_t *z)
{
	if (z == NULL)
		return;

	free(z);
}

complex_t *complex_fromString(const char *str)
{
	char **fragments = NULL, *iterator = NULL, *i = NULL, *tmp = NULL;
	complex_t *z = NULL;
	double re = 0.0, im = 0.0;
	size_t nbrFragments = 0, size = 0;
	char number = 0;

	if (str == NULL)
		return NULL;

	fragments = split(str, ' ', &nbrFragments);
	if (fragments == NULL)
		return NULL;

	if (nbrFragments == 3)
	{
		// On convertit les chaînes de caractères en nombre
		re = atof(fragments[0]);
		
		if (!strcmp(fragments[2], "i"))
			im = 1.0;
		else
			im = atof(fragments[2] + 1);

		z = (!strcmp(fragments[1], "-")) ? complex_init(re, -im) : complex_init(re, im);
	}
	else if (nbrFragments == 2)
	{
		// On recherche si il y a un i présent dans le nombre
		i = strchr(fragments[1], 'i');
		if (i != NULL)
		{
			size = 1;
			tmp = (char*) malloc(sizeof(char));
			iterator = fragments[1];

			while (*iterator != '\0')
			{
				if (iterator != i)
				{
					if (*iterator >= '0' && *iterator <= '9')
						number = 1;

					tmp[size - 1] = *iterator;

					size++;
					tmp = (char*) realloc(tmp, size * sizeof(char));
				}

				iterator++;
			}

			if (!number)
			{
				tmp[size - 1] = '1';

				size++;
				tmp = (char*) realloc(tmp, size * sizeof(char));
			}

			tmp[size - 1] = '\0';

			z = (!strcmp(fragments[0], "-")) ? complex_init(0.0, -atof(tmp)) : complex_init(0.0, atof(tmp));
			free(tmp);
		}
		else
			z = (!strcmp(fragments[0], "-")) ? complex_init(atof(fragments[1]), 0.0) : complex_init(atof(fragments[1]), 0.0);
	}
	else if (nbrFragments == 1)
	{
		// On recherche si il y a un i présent dans le nombre
		i = strchr(*fragments, 'i');
		if (i != NULL)
		{
			size = 1;
			tmp = (char*) malloc(sizeof(char));
			iterator = *fragments;

			while (*iterator != '\0')
			{
				if (iterator != i)
				{
					if (*iterator >= '0' && *iterator <= '9')
						number = 1;

					tmp[size - 1] = *iterator;

					size++;
					tmp = (char*) realloc(tmp, size * sizeof(char));
				}

				iterator++;
			}

			if (!number)
			{
				tmp[size - 1] = '1';

				size++;
				tmp = (char*) realloc(tmp, size * sizeof(char));
			}

			tmp[size - 1] = '\0';
			im = atof(tmp);

			z = complex_init(0.0, im);
			free(tmp);
		}
		else
			z = complex_init(atof(*fragments), 0.0);
	}

	return z;
}

char *complex_toString(complex_t *z, unsigned int precision)
{
	char tmp[512] = { 0 };
	char *str = NULL;

	if (z == NULL)
		return NULL;

	if (precision > 0)
	{
		if (z->re == 0.0 && z->im == 0.0)
			sprintf(tmp, "0");
	    if (z->re == 0.0)
            sprintf(tmp, "i %.*lf", precision, z->im);
        else if (z->im == 0.0)
            sprintf(tmp, "%.*lf", precision, z->re);
        else
            sprintf(tmp, "%.*lf + i %.*lf", precision, z->re, precision, z->im);
	}
    else
    {
		if (z->im == 0.0 && z->re == 0.0)
			sprintf(tmp, "0");
        else if (z->im == 0.0)
            sprintf(tmp, "%.2lf", z->re);
        else if (z->re == 0.0)
            sprintf(tmp, "i %.2lf", z->im);
        else
            sprintf(tmp, "%.2lf + i %.2lf", z->re, z->im);
    }


	str = (char*) malloc((strlen(tmp) + 1) * sizeof(char));
	strcpy(str, tmp);

	return str;
}

complex_t *complex_conj(complex_t *z)
{
	return complex_init(z->re, -1.0 * z->im);
}

double complex_arg(complex_t *z)
{
	return acos(z->re / z->mod);
}

char complex_compare(complex_t *a, complex_t *b)
{
	// Mesure de sécurité
	if (a == NULL || b == NULL)
		return 0;

	// Si les parties réelles et imaginaires sont égales, on renvoit vrai
	return (a->re == b->re && a->im == b->im) ? 1 : 0;
}

complex_t *complex_sum(complex_t *a, complex_t *b)
{
	// Mesure de sécurité
	if (a == NULL || b == NULL)
		return NULL;

	// On effectue les sommes, on alloue en mémoire le nouveau complexe et on renvoit son adresse
	return complex_init(a->re + b->re, a->im + b->im);
}

complex_t *complex_diff(complex_t *a, complex_t *b)
{
	// Mesure de sécurité
	if (a == NULL || b == NULL)
		return NULL;

	// On effectue les différences, on alloue en mémoire le nouveau complexe et on renvoit son adresse
	return complex_init(a->re - b->re, a->im - b->im);
}

complex_t *complex_scalarProd(double k, complex_t *z)
{
	// Mesure de sécurité
	if (z == NULL)
		return NULL;

	// On effectue le produit, on alloue en mémoire le nouveau complexe et on renvoit son adresse
	return complex_init(k * z->re, k * z->im);
}

complex_t *complex_prod(complex_t *a, complex_t *b)
{
	// Mesure de sécurité
	if (a == NULL || b == NULL)
		return NULL;

	// On effectue la somme et la différence du produit, on alloue en mémoire le nouveau complexe et on renvoit son adresse
	return complex_init(a->re * b->re - a->im * b->im, a->re * b->im + a->im * b->re);
}

complex_t *complex_reverse(complex_t *z)
{
	double denom = 0.0;

	if (z == NULL || (z->re == 0.0 && z->im == 0.0))
		return NULL;

	denom = z->re * z->re + z->im * z->im;

	return complex_init(z->re / denom, (-1.0 * z->im) / denom);
}

complex_t *complex_pow(complex_t *z, long n)
{
	complex_t *y = NULL, *tmp = NULL;
	unsigned long degree = labs(n);

	if (z == NULL)
		return NULL;
	else if (degree == 0)
		return complex_init(1.0, 0.0);

	if (degree % 2 == 0)
	{
		y = complex_pow(z, degree / 2);
		if (y == NULL)
			return NULL;

		tmp = complex_init(y->re * y->re - y->im * y->im, 2.0 * y->re * y->im);
		if (tmp == NULL)
		{
			complex_free(y);

			return NULL;
		}

		complex_free(y);
		y = tmp;
	}
	else
	{
		y = complex_pow(z, degree - 1);
		if (y == NULL)
			return NULL;

		tmp = complex_prod(z, y);
		if (tmp == NULL)
		{
			complex_free(y);

			return NULL;
		}

		complex_free(y);
		y = tmp;
	}

	if (n < 0)
	{
		tmp = complex_reverse(y);
		if (tmp == NULL)
		{
			complex_free(y);

			return NULL;
		}

		complex_free(y);
		y = tmp;
	}

	return y;
}

complex_t *complex_scalarDiv(complex_t *z, double k)
{
	// Mesure de sécurité
	if (z == NULL || k == 0.0)
		return NULL;

	// On effectue la division, on alloue le nouveau complexe et on renvoit son adresse
	return complex_init(z->re / k, z->im / k);
}

complex_t *complex_div(complex_t *a, complex_t *b)
{
	double denom = 0.0;

	// Mesure de sécurité
	if (a == NULL || b == NULL || (b->re == 0.0 && b->im == 0.0))
		return NULL;

	// On calcule b * ¬b
	denom = b->re * b->re + b->im * b->im;

	// On effectue la somme et la différence du produit, on divise les parties par denom puis,
	// on alloue en mémoire le nouveau complexe et on revoit son adresse
	return complex_init((a->re * b->re + a->im * b->im) / denom, (a->im * b->re - a->re * b->im) / denom);
}
