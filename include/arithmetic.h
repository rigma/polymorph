#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include "type/polynomial.h"

/**
 * @fn     polynomial_sum(polynomial_t *p, polynomial_t *q)
 * @author Romain Failla
 * @brief  Réalise dans C[X] p + q
 * @param  polynomial_t *p : l'adresse du premier polynôme de la somme
 * @param  polynomial_t *q : l'adresse du second polynôme de la somme
 * @param  const char *name : le nom du produit (laissé à NULL pour un nom automatique)
 * @return polynomial_t* : l'adresse du résultat
 */
polynomial_t *polynomial_sum(polynomial_t *p, polynomial_t *q, const char *name);

/**
 * @fn     polynomial_diff(polynomial_t *p, polynomial_t *q)
 * @author Romain Failla
 * @brief  Réalise dans C[X] p - q
 * @param  polynomial_t *p : l'adresse du premier polynôme de la différence
 * @param  polynomial_t *q : l'adresse du second polynôme de la différence
 * @param  const char *name : le nom du produit (laissé à NULL pour un nom automatique)
 * @return polynomial_t* : l'adresse du résultat
 */
polynomial_t *polynomial_diff(polynomial_t *p, polynomial_t *q, const char *name);

/**
 * @fn     polynomial_scalarProduct(complex_t *k, polynomial_t *p)
 * @author Romain Failla
 * @brief  Réalise dans C[X] k * p
 * @param  complex_t *k : le scalaire du produit
 * @param  polynomial_t *p : le polynôme du produit
 * @param  const char *name : le nom du produit (laissé à NULL pour un nom automatique)
 * @return polynomial_t* : l'adresse du résultat
 */
polynomial_t *polynomial_scalarProduct(complex_t *k, polynomial_t *p, const char *name);

/**
 * @fn     polynomial_prod(polynomial_t *p, polynomial_t *q)
 * @author Romain Failla | Etienne Quelain
 * @brief  Réalise p * q
 * @param  polynomial_t *p : le premier polynôme du produit
 * @param  polynomial_t *q : le second polynôme du produit
 * @param  const char *name : le nom du produit (laissé à NULL pour un nom automatique)
 * @return polynomial_t* : l'adresse du résultat
 */
polynomial_t *polynomial_prod(polynomial_t *p, polynomial_t *q, const char *name);

/**
 * @fn     polynomial_pow(polynomial_t *p, long n)
 * @author Romain Failla
 * @brief  Réalise p^n
 * @param  polynomial_t *p : le polynôme à élever à la puissance n
 * @param  long n : la puissance de l'exponentiation
 * @return polynomial_t*
 */
polynomial_t *polynomial_pow(polynomial_t *p, long n);

#endif
