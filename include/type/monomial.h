#ifndef MONOMIAL_H
#define MONOMIAL_H

#include "complex.h"

/**
 * @struct monomial_t
 * @author Romain Failla
 * @brief  Représente un monôme en mémoire
 */
typedef struct monomial_t {
	unsigned long degree;
	complex_t *coef;
	struct monomial_t *previous;
	struct monomial_t *next;
} monomial_t;

/**
 * @fn     monomial_init(complex_t *coef, unsigned int pow)
 * @author Romain Failla
 * @brief  Initialise une structure monomial_t en mémoire
 * @param  complex_t *coef : le coefficient du monôme
 * @param  unsigned long degree : le degré du monôme
 * @return monomial_t* : l'adresse du nouveau monôme
 */
monomial_t *monomial_init(complex_t *coef, unsigned long degree);

/**
 * @fn     monomial_free(monomial_t *m)
 * @author Romain Failla
 * @brief  Libère un monôme de la mémoire
 * @param  monomial_t *m : la structure à libérer de la mémoire
 */
void monomial_free(monomial_t *m);

/**
 * @fn     monomial_display(monomial_t *m)
 * @author Étienne Quélain
 * @brief  Affiche un monôme
 * @param  monomial_t *m : l'adresse du monôme à afficher
 */
void monomial_display(monomial_t *m);

/**
 * @fn     monomial_eval(monomial_t *m, double x)
 * @author Romain Failla
 * @brief  Renvoie le résultat complexe de l'évaluation en x du monôme
 * @param  monomial_t *m : l'adresse du monôme à évaluer
 * @param  double x : la valeur d'évaluation
 * @return complex_t* : l'adresse du résultat de l'évaluation
 */
complex_t *monomial_eval(monomial_t *m, double x);

#endif
