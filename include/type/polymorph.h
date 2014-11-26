#ifndef POLYMORPH_H
#define POLYMORPH_H

#include "polynomial.h"

// TODO : rajouter les autres fonctions rattach�es � la gestion des structures polymorph_t

/**
 * @struct polymorph_t
 * @author Romain Failla
 * @brief  Repr�sente un polyn�me sous forme factoris�
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

/**
 * @fn     polymorph_append(polymorph_t *p, complex_t *root)
 * @author Romain Failla
 * @brief  Ajoute une nouvelle racine au polyn�me
 * @param  polymorph_t *p : le polyn�me de destination
 * @param  complex_t *root : la valeur de la racine
 */
void polymorph_append(polymorph_t *p, complex_t *root);

/**
 * @fn     polymorph_remove(polymorph_t *p, complex_t *root)
 * @author Romain Failla
 * @brief  Enl�ve toutes les racines d�sign�s du polyn�me
 * @param  polymorph_t *p : le polyn�me de travail
 * @param  complex_t *root : la racine a enlev�
 */
void polymorph_remove(polymorph_t *p, complex_t *root);

/**
 * @fn     polymorph_evalFromTable(complex_t *a, size_t nbrRoots, complex_t **roots, complex_t *eval)
 * @author Romain Failla
 * @brief  R�alise l'�valuation en un nombre donn� d'un polyn�me sous forme factoris� d�fini � l'aide du tableau roots
 * @param  complex_t *a : le coefficient principal du polyn�me
 * @param  size_t nbrRoots : le nombre de racines de la table
 * @param  complex_t **roots : les racines qui servent � d�finir le polyn�me
 * @param  complex_t *eval : le point de l'�valuation
 * @return complex_t*
 */
complex_t *polymorph_evalFromTable(complex_t *a, size_t nbrRoots, complex_t **roots, complex_t *eval);

#endif
