#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include "monomial.h"

/**
 * @struct polynomial_t
 * @author Romain Failla
 * @brief  Représente un polynôme sous forme développé
 */
typedef struct polynomial_t {
	unsigned long degree;
	unsigned long size;
	unsigned long pow;
	char *name;
	monomial_t *first;
	monomial_t *last;
	struct polynomial_t *previous;
	struct polynomial_t *next;
} polynomial_t;

/**
 * @fn     polynomial_init(const char *name)
 * @author Romain Failla
 * @brief  Initialise une structure polynomial_t en mémoire
 * @param  const char *name : le nom du polynôme
 * @return polynomial_t* : l'adresse du nouveau polynôme
 */
polynomial_t *polynomial_init(const char *name);

/**
 * @fn     polynomial_free(polynomial_t *p)
 * @author Romain Failla
 * @brief  Libère un polynôme de la mémoire
 * @param  polynomial_t *p : l'adresse du polynôme à libérer
 */
void polynomial_free(polynomial_t *p);

/**
 * @fn     polynomial_display(polynomial_t *p)
 * @author Étienne Quélain
 * @brief  Affiche le polynôme p
 * @param  polynomial_t *p : l'adresse du polynôme à afficher
 */
void polynomial_display(polynomial_t *p);

/**
 * @fn     polynomial_eval(complex_t *coef, monomial_t *m, complex_t *eval)
 * @author Romain Failla
 * @brief  Réalise l'évaluation d'un polynôme sous forme développée en eval
 * @param  polynomial_t *p : l'adresse du polynôme évalué
 * @param  complex_t *coef : l'adresse du coefficient de l'évaluation
 * @param  monomial_t *m : l'adresse du monôme courant du polynôme
 * @param  complex_t *eval : la valeur de l'évaluation
 * @return complex_t*
 */
complex_t *polynomial_eval(polynomial_t *p, complex_t *coef, monomial_t *m, complex_t *eval);

/**
 * @fn     polynomial_reduce(polynomial_t *p, unsigned long n)
 * @author Étienne QUÉLAIN
 * @brief  Factorise un polynôme par X^n
 * @param  polynomial_t *p : l'adresse du polynôme de travail
 * @param  unsigned long n : le degré de factorisation
 */
void polynomial_reduce(polynomial_t *p, unsigned long n);

/**
 * @fn     polynomial_reduce(polynomial_t *p, unsigned long n)
 * @author Étienne QUÉLAIN
 * @brief  Développe p(X) * X^n
 * @param  polynomial_t *p : l'adresse du polynôme de travail
 * @param  unsigned long n : le degré de factorisation
 */
void polynomial_increase(polynomial_t *p, unsigned long n);

/**
 * @fn     polynomial_insert(polynomial_t *p, monomial_t *m)
 * @author Romain Failla
 * @brief  Insère dans un polynôme un nouveau monôme
 * @param  polynomial_t *p : l'adresse du polynôme de destination
 * @param  monomial_t *m : l'adresse du monôme à ajouter
 */
void polynomial_insert(polynomial_t *p, monomial_t *m);

/**
 * @fn     polynomial_append(polynomial_t *p, complex_t *coef, unsigned long degree)
 * @author Romain Failla
 * @brief  Ajoute un nouveau monôme au polynôme sélectionné
 * @param  polynomial_t *p : l'adresse du polynôme de destination
 * @param  complex_t *coef : l'adresse du coefficient du polynôme
 * @param  unsigned long degree : la puissance du monôme
 */
void polynomial_append(polynomial_t *p, complex_t *coef, unsigned long degree);

/**
 * @fn     polynomial_extract(polynomial_t *p, unsigned long degree, unsigned long end)
 * @author Romain Failla
 * @brief  Extrait les monômes du degré degree jusqu'au degré end du polynôme sélectionné
 * @param  polynomial_t *p : l'adresse du polynôme d'extraction
 * @param  unsigned long degree : le degré de départ de l'extraction
 * @param  unsigned long end : le degré d'arrivé de l'extraction
 * @return polynomial_t*
 */
polynomial_t *polynomial_extract(polynomial_t *p, unsigned long degree, unsigned long end);

/**
 * @fn     polynomial_extractReal(polynomial_t *p)
 * @author Romain Failla
 * @brief  Extrait la partie réelle du polynôme donné
 * @param  polynomial_t *p : le polynôme d'extraction
 * @return polynomial_t*
 */
polynomial_t *polynomial_extractReal(polynomial_t *p);

/**
* @fn     polynomial_extractImaginary(polynomial_t *p)
* @author Romain Failla
* @brief  Extrait la partie imaginaire du polynôme donné
* @param  polynomial_t *p : le polynôme d'extraction
* @return polynomial_t*
*/
polynomial_t *polynomial_extractImaginary(polynomial_t *p);

/**
 * @fn     polynomial_remove(polynomial_t *p, unsigned long degree)
 * @author Romain Failla
 * @brief  Enlève le monôme d'un degré donné du polynôme
 * @param  polynimial_t *p : l'adresse du polynôme de travail
 * @param  unsigned long degree : le degré du monôme
 */
void polynomial_remove(polynomial_t *p, unsigned long degree);

#endif
