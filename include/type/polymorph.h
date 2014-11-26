#ifndef POLYMORPH_H
#define POLYMORPH_H

#include "polynomial.h"

// TODO : rajouter les autres fonctions rattachées à la gestion des structures polymorph_t

/**
 * @struct polymorph_t
 * @author Romain Failla
 * @brief  Représente un polynôme sous forme factorisé
 */
typedef struct {
	complex_t *a;
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

/**
 * @fn     polymorph_append(polymorph_t *p, complex_t *root)
 * @author Romain Failla
 * @brief  Ajoute une nouvelle racine au polynôme
 * @param  polymorph_t *p : le polynôme de destination
 * @param  complex_t *root : la valeur de la racine
 */
void polymorph_append(polymorph_t *p, complex_t *root);

/**
 * @fn     polymorph_remove(polymorph_t *p, complex_t *root)
 * @author Romain Failla
 * @brief  Enlève toutes les racines désignés du polynôme
 * @param  polymorph_t *p : le polynôme de travail
 * @param  complex_t *root : la racine a enlevé
 */
void polymorph_remove(polymorph_t *p, complex_t *root);

/**
 * @fn     polymorph_evalFromTable(complex_t *a, size_t nbrRoots, complex_t **roots, complex_t *eval)
 * @author Romain Failla
 * @brief  Réalise l'évaluation en un nombre donné d'un polynôme sous forme factorisé défini à l'aide du tableau roots
 * @param  complex_t *a : le coefficient principal du polynôme
 * @param  size_t nbrRoots : le nombre de racines de la table
 * @param  complex_t **roots : les racines qui servent à définir le polynôme
 * @param  complex_t *eval : le point de l'évaluation
 * @return complex_t*
 */
complex_t *polymorph_evalFromTable(complex_t *a, size_t nbrRoots, complex_t **roots, complex_t *eval);

#endif
