#ifndef ANALYSIS_H
#define ANALYSIS_H

#include "type/polynomial.h"
#include "type/polymorph.h"

#define ROOTS_MAX_COUNT 999
#define ROOTS_EPSILON   1e-15

/**
 * @fn     polynomial_differentiate(polynomial_t *p)
 * @author Romain Failla
 * @brief  R�alise la d�riv�e du polyn�me d�velopp� p
 * @param  polynomial_t *p : l'adresse du polyn�me � d�riv�e
 * @return polynomial_t*
 */
polynomial_t *polynomial_differentiate(polynomial_t *p);

/**
 * @fn     polynomial_integrate(polynomial_t *p, complex_t *c)
 * @author Romain Failla
 * @brief  R�alise la primitive du polyn�me d�velopp� p
 * @param  polynomial_t *p : l'adresse du polyn�me � primitiver
 * @param  complex_t *c : la constante de primitivisation (vous pouvez la laisser � NULL)
 * @return polynomial_t*
 */
polynomial_t *polynomial_integrate(polynomial_t *p, complex_t *c);

/**
 * @fn     polynomial_zeros_DurandKerner(polynomial_t *p)
 * @author Romain Failla
 * @brief  D�termine des "bons" points de d�part, � l'aide de la m�thode de Durand-Kerner-Weierstrass, pour la m�thode d'Aberth-Ehrlich pour un degr� donn�
 * @param  polynomial_t *p : le polyn�me qui subit l'approximation
 * @return complex_t**
 */
complex_t **polynomial_zeros_DurandKerner(polynomial_t *p);

/**
 * @fn     polynomial_zeros(polynomial_t *p)
 * @author Romain Failla
 * @brief  Effectue l'approximation des racines du polyn�mes et les renvoies dans un polyn�me sous forme factoris�e en utilisant la m�thode d'Aberth-Ehrlich
 * @param  polynomial_t *p : le polyn�me � analyser
 * @return polymorph_t*
 */
polymorph_t *polynomial_zeros(polynomial_t *p);

#endif
