#ifndef ANALYSIS_H
#define ANALYSIS_H

#include "type/polynomial.h"
#include "type/polymorph.h"

#define ROOTS_MAX_COUNT 999
#define ROOTS_EPSILON   1e-15

/**
 * @fn     polynomial_differentiate(polynomial_t *p)
 * @author Romain Failla
 * @brief  Réalise la dérivée du polynôme développé p
 * @param  polynomial_t *p : l'adresse du polynôme à dérivée
 * @return polynomial_t*
 */
polynomial_t *polynomial_differentiate(polynomial_t *p);

/**
 * @fn     polynomial_integrate(polynomial_t *p, complex_t *c)
 * @author Romain Failla
 * @brief  Réalise la primitive du polynôme développé p
 * @param  polynomial_t *p : l'adresse du polynôme à primitiver
 * @param  complex_t *c : la constante de primitivisation (vous pouvez la laisser à NULL)
 * @return polynomial_t*
 */
polynomial_t *polynomial_integrate(polynomial_t *p, complex_t *c);

/**
 * @fn     polynomial_zeros_DurandKerner(polynomial_t *p)
 * @author Romain Failla
 * @brief  Détermine des "bons" points de départ, à l'aide de la méthode de Durand-Kerner-Weierstrass, pour la méthode d'Aberth-Ehrlich pour un degré donné
 * @param  polynomial_t *p : le polynôme qui subit l'approximation
 * @return complex_t**
 */
complex_t **polynomial_zeros_DurandKerner(polynomial_t *p);

/**
 * @fn     polynomial_zeros(polynomial_t *p)
 * @author Romain Failla
 * @brief  Effectue l'approximation des racines du polynômes et les renvoies dans un polynôme sous forme factorisée en utilisant la méthode d'Aberth-Ehrlich
 * @param  polynomial_t *p : le polynôme à analyser
 * @return polymorph_t*
 */
polymorph_t *polynomial_zeros(polynomial_t *p);

#endif
