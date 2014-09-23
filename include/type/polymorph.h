#ifndef POLYMORPH_H
#define POLYMORPH_H

#include "polynomial.h"

/**
 * @struct polymorph_t
 * @author Romain Failla
 * @brief  Représente un polynôme sous forme factorisé
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
 * @brief  Alloue en mémoire une structure polymorph
 * @param  const char *name : le nom du polynôme factorisé
 * @return polymorph_t* : l'adresse du polynôme factorisé alloué en mémoire
 */
polymorph_t *polymorph_init(const char *name);

/**
 * @fn     polymorph_free(polymorph_t *p)
 * @author Romain Failla
 * @brief  Libère de la mémoire une structure polymorph_t
 * @param  polymorph_t *p : l'adresse du polynôme factorisé à libérer
 */
void polymorph_free(polymorph_t *p);

#endif
