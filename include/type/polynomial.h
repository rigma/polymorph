#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include "monomial.h"

/**
 * @struct polynomial_t
 * @author Romain Failla
 * @brief  Repr�sente un polyn�me sous forme d�velopp�
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
 * @brief  Initialise une structure polynomial_t en m�moire
 * @param  const char *name : le nom du polyn�me
 * @return polynomial_t* : l'adresse du nouveau polyn�me
 */
polynomial_t *polynomial_init(const char *name);

/**
 * @fn     polynomial_free(polynomial_t *p)
 * @author Romain Failla
 * @brief  Lib�re un polyn�me de la m�moire
 * @param  polynomial_t *p : l'adresse du polyn�me � lib�rer
 */
void polynomial_free(polynomial_t *p);

/**
 * @fn     polynomial_append(polynomial_t *p, complex_t *coef, unsigned long degree)
 * @author Romain Failla
 * @brief  Ajoute un nouveau mon�me au polyn�me s�lectionn�
 * @param  polynomial_t *p : l'adresse du polyn�me de destination
 * @param  complex_t *coef : l'adresse du coefficient du polyn�me
 * @param  unsigned long degree : la puissance du mon�me
 */
void polynomial_append(polynomial_t *p, complex_t *coef, unsigned long degree);

/**
 * @fn     polynomial_insert(polynomial_t *p, monomial_t *m)
 * @author Romain Failla
 * @brief  Ins�re dans un polyn�me un nouveau mon�me
 * @param  polynomial_t *p : l'adresse du polyn�me de destination
 * @param  monomial_t *m : l'adresse du mon�me � ajouter
 */
void polynomial_insert(polynomial_t *p, monomial_t *m);

/**
 * @fn     polynomial_remove(polynomial_t *p, unsigned long degree)
 * @author Romain Failla
 * @brief  Enl�ve le mon�me d'un degr� donn� du polyn�me
 * @param  polynimial_t *p : l'adresse du polyn�me de travail
 * @param  unsigned long degree : le degr� du mon�me
 */
void polynomial_remove(polynomial_t *p, unsigned long degree);

#endif
