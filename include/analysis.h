#ifndef ANALYSIS_H
#define ANALYSIS_H

#include <type/polynomial.h>

/**
 * @fn     polynomial_differentiate(polynomial_t *p)
 * @author Romain Failla
 * @brief  R�alise la d�riv�e du polyn�me d�velopp� p
 * @param  polynomial_t *p : l'adresse du polyn�me � d�riv�e
 * @return polynomial_t*
 */
polynomial_t *polynomial_differentiate(polynomial_t *p);

#endif
