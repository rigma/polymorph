#ifndef MONOMIAL_H
#define MONOMIAL_H

#include "complex.h"

/**
 * @struct monomial_t
 * @author Romain Failla
 * @brief  Repr�sente un mon�me en m�moire
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
 * @brief  Initialise une structure monomial_t en m�moire
 * @param  complex_t *coef : le coefficient du mon�me
 * @param  unsigned long degree : le degr� du mon�me
 * @return monomial_t* : l'adresse du nouveau mon�me
 */
monomial_t *monomial_init(complex_t *coef, unsigned long degree);

/**
 * @fn     monomial_free(monomial_t *m)
 * @author Romain Failla
 * @brief  Lib�re un mon�me de la m�moire
 * @param  monomial_t *m : la structure � lib�rer de la m�moire
 */
void monomial_free(monomial_t *m);

/**
 * @fn     monomial_display(monomial_t *m)
 * @author �tienne Qu�lain
 * @brief  Affiche un mon�me
 * @param  monomial_t *m : l'adresse du mon�me � afficher
 */
void monomial_display(monomial_t *m);

/**
 * @fn     monomial_eval(monomial_t *m, double x)
 * @author Romain Failla
 * @brief  Renvoie le r�sultat complexe de l'�valuation en x du mon�me
 * @param  monomial_t *m : l'adresse du mon�me � �valuer
 * @param  double x : la valeur d'�valuation
 * @return complex_t* : l'adresse du r�sultat de l'�valuation
 */
complex_t *monomial_eval(monomial_t *m, double x);

#endif
