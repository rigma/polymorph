#ifndef ANALYSIS_H
#define ANALYSIS_H

#include <type/polynomial.h>

/**
 * @fn     polynomial_differentiate(polynomial_t *p)
 * @author Romain Failla
 * @brief  Réalise la dérivée du polynôme développé p
 * @param  polynomial_t *p : l'adresse du polynôme à dérivée
 * @return polynomial_t*
 */
polynomial_t *polynomial_differentiate(polynomial_t *p);

#endif
