#ifndef POLYMORPH_H
#define POLYMORPH_H

#include "polynomial.h"

/**
 * @struct polymorph_t
 * @author Romain Failla
 * @brief  Repr�sente un polyn�me sous forme factoris�
 */
typedef struct {
	unsigned long size;
	char *name;
	polynomial_t *first;
	polynomial_t *last;
} polymorph_t;

/**
 * @fn     polymorph_init(const char *name)
 * @author Romain Failla
 * @brief  Alloue en m�moire une structure polymorph
 * @param  const char *name : le nom du polyn�me factoris�
 * @return polymorph_t* : l'adresse du polyn�me factoris� allou� en m�moire
 */
polymorph_t *polymorph_init(const char *name);

/**
 * @fn     polymorph_free(polymorph_t *p)
 * @author Romain Failla
 * @brief  Lib�re de la m�moire une structure polymorph_t
 * @param  polymorph_t *p : l'adresse du polyn�me factoris� � lib�rer
 */
void polymorph_free(polymorph_t *p);

#endif
