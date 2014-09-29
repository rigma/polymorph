#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include "type/polynomial.h"

/**
 * @fn     polynomial_sum(polynomial_t *p, polynomial_t *q)
 * @author Romain Failla
 * @brief  Réalise dans C[X] p + q
 * @param  polynomial_t *p : l'adresse du premier polynôme de la somme
 * @param  polynomial_t *q : l'adresse du second polynôme de la somme
 * @return polynomial_t* : l'adresse du résultat
 */
polynomial_t *polynomial_sum(polynomial_t *p, polynomial_t *q);

/**
 * @fn     polynomial_diff(polynomial_t *p, polynomial_t *q)
 * @author Romain Failla
 * @brief  Réalise dans C[X] p - q
 * @param  polynomial_t *p : l'adresse du premier polynôme de la différence
 * @param  polynomial_t *q : l'adresse du second polynôme de la différence
 * @return polynomial_t* : l'adresse du résultat
 */
polynomial_t *polynomial_diff(polynomial_t *p, polynomial_t *q);

/**
 * @fn     polynomial_scalarProduct(complex_t *k, polynomial_t *p)
 * @author Romain Failla
 * @brief  Réalise dans C[X] k * p
 * @param  complex_t *k : le scalaire du produit
 * @param  polynomial_t *p : le polynôme du produit
 * @return polynomial_t* : l'adresse du résultat
 */
polynomial_t *polynomial_scalarProduct(complex_t *k, polynomial_t *p);

/**
 * @fn     polynomial_prod(polynomial_t *p, polynomial_t *q)
 * @author Etienne Quelain
 * @brief  Réalise p * q
 * @param  polynomial_t *p : le premier polynôme du produit
 * @param  polynomial_t *q : le second polynôme du produit
 * @return polynomial_t* : l'adresse du résultat
 */
polynomial_t *polynomial_prod(polynomial_t *p, polynomial_t *q);

#endif
