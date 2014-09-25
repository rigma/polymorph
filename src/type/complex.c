#include <stdlib.h>
#include <math.h>

#include <type/complex.h>

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
	free(z);
}

complex_t *complex_conj(complex_t *z)
{
	return complex_init(z->re, -1.0 * z->im);
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
