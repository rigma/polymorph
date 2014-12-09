#ifndef ARITHMETIC_H
#define ARITHMETIC_H

#include "type/polynomial.h"
#include "io/manager.h"

/**
 * @fn     polynomial_sum(polynomial_t *p, polynomial_t *q)
 * @author Romain Failla
 * @brief  R�alise dans C[X] p + q
 * @param  polynomial_t *p : l'adresse du premier polyn�me de la somme
 * @param  polynomial_t *q : l'adresse du second polyn�me de la somme
 * @param  const char *name : le nom du produit (laiss� � NULL pour un nom automatique)
 * @return polynomial_t* : l'adresse du r�sultat
 */
polynomial_t *polynomial_sum(polynomial_t *p, polynomial_t *q, const char *name);

/**
 * @fn     polynomial_diff(polynomial_t *p, polynomial_t *q)
 * @author Romain Failla
 * @brief  R�alise dans C[X] p - q
 * @param  polynomial_t *p : l'adresse du premier polyn�me de la diff�rence
 * @param  polynomial_t *q : l'adresse du second polyn�me de la diff�rence
 * @param  const char *name : le nom du produit (laiss� � NULL pour un nom automatique)
 * @return polynomial_t* : l'adresse du r�sultat
 */
polynomial_t *polynomial_diff(polynomial_t *p, polynomial_t *q, const char *name);

/**
 * @fn     polynomial_scalarProduct(complex_t *k, polynomial_t *p)
 * @author Romain Failla
 * @brief  R�alise dans C[X] k * p
 * @param  complex_t *k : le scalaire du produit
 * @param  polynomial_t *p : le polyn�me du produit
 * @param  const char *name : le nom du produit (laiss� � NULL pour un nom automatique)
 * @return polynomial_t* : l'adresse du r�sultat
 */
polynomial_t *polynomial_scalarProduct(complex_t *k, polynomial_t *p, const char *name);

/**
 * @fn     polynomial_prod(polynomial_t *p, polynomial_t *q)
 * @author Romain Failla | Etienne Quelain
 * @brief  R�alise p * q
 * @param  polynomial_t *p : le premier polyn�me du produit
 * @param  polynomial_t *q : le second polyn�me du produit
 * @param  const char *name : le nom du produit (laiss� � NULL pour un nom automatique)
 * @return polynomial_t* : l'adresse du r�sultat
 */
polynomial_t *polynomial_prod(polynomial_t *p, polynomial_t *q, const char *name);

/**
 * @fn     polynomial_pow(polynomial_t *p, long n)
 * @author Romain Failla
 * @brief  R�alise p^n
 * @param  polynomial_t *p : le polyn�me � �lever � la puissance n
 * @param  long n : la puissance de l'exponentiation
 * @return polynomial_t*
 */
polynomial_t *polynomial_pow(polynomial_t *p, long n);

/**
 * @fn     polynomial_interpreter(void *result, entry_t *list, char *str)
 * @author Romain Failla
 * @brief  Interpr�te la cha�ne de caract�re comme une expression avec des polyn�mes
 * @param  void *result : l'adresse du stockage du r�sultat
 * @param  entry_t *list : la liste des polyn�mes d�finis en m�moire
 * @param  char *str : la cha�ne de caract�res � interpr�ter
 * @return int : retourne 1 si c'est un complexe, 0 sinon
 */
int polynomial_interpreter(void *result, entry_t *list, char *str);

#endif
