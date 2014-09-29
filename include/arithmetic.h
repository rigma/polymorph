#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include "type/polynomial.h"

/**
 * @fn     polynomial_sum(polynomial_t *p, polynomial_t *q)
 * @author Romain Failla
 * @brief  R�alise dans C[X] p + q
 * @param  polynomial_t *p : l'adresse du premier polyn�me de la somme
 * @param  polynomial_t *q : l'adresse du second polyn�me de la somme
 * @return polynomial_t* : l'adresse du r�sultat
 */
polynomial_t *polynomial_sum(polynomial_t *p, polynomial_t *q);

/**
 * @fn     polynomial_diff(polynomial_t *p, polynomial_t *q)
 * @author Romain Failla
 * @brief  R�alise dans C[X] p - q
 * @param  polynomial_t *p : l'adresse du premier polyn�me de la diff�rence
 * @param  polynomial_t *q : l'adresse du second polyn�me de la diff�rence
 * @return polynomial_t* : l'adresse du r�sultat
 */
polynomial_t *polynomial_diff(polynomial_t *p, polynomial_t *q);

/**
 * @fn     polynomial_scalarProduct(complex_t *k, polynomial_t *p)
 * @author Romain Failla
 * @brief  R�alise dans C[X] k * p
 * @param  complex_t *k : le scalaire du produit
 * @param  polynomial_t *p : le polyn�me du produit
 * @return polynomial_t* : l'adresse du r�sultat
 */
polynomial_t *polynomial_scalarProduct(complex_t *k, polynomial_t *p);

/**
 * @fn     polynomial_prod(polynomial_t *p, polynomial_t *q)
 * @author Etienne Quelain
 * @brief  R�alise p * q
 * @param  polynomial_t *p : le premier polyn�me du produit
 * @param  polynomial_t *q : le second polyn�me du produit
 * @return polynomial_t* : l'adresse du r�sultat
 */
polynomial_t *polynomial_prod(polynomial_t *p, polynomial_t *q);

#endif
