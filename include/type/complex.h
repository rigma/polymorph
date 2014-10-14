#ifndef COMPLEX_H
#define COMPLEX_H

/**
 * @struct complex_t
 * @author Romain FAILLA
 * @brief  Représente un nombre complexe en mémoire
 */
typedef struct {
	double re;  // la partie réelle
	double im;  // la partie imaginaire
	double mod; // Le module du complexe
} complex_t;

/**
 * @fn     complex_init(double re, double im)
 * @author Romain Failla
 * @brief  Initialise en mémoire une structure complex_t
 * @param  double re : la partie réelle du nouveau complexe
 * @param  double im : la partie imaginaire du nouveau complexe
 * @return complex_t* : l'adresse du nouveau complexe
 */
complex_t *complex_init(double re, double im);

/**
 * @fn     complex_free(complex_t *z)
 * @author Romain Failla
 * @brief  Libère de la mémoire une structure complex_t
 * @param  complex_t *z : l'adresse de la structure à libérer
 */
void complex_free(complex_t *z);

/**
 * @fn     complex_display(complex_t *z)
 * @brief  Renvoi une chaîne de caractère représentant le nombre complexe
 * @author Romain Failla
 * @param  complex_t *z : l'adresse du nombre complexe à afficher
 * @param  unsigned int precision : la précision de l'écriture (mettre à 0 pour la valeur par défaut)
 * @return char*
 */
char *complex_display(complex_t *z, unsigned int precision);

/**
 * @fn     complex_conj(complex_t *z)
 * @brief  Renvoi l'adresse du conjugué de z qui est alloué en mémoire
 * @author Romain Failla
 * @param  complex_t *z : l'adresse du nombre complexe traité
 * @return complex_t* : l'adresse du conjugué
 */
complex_t *complex_conj(complex_t *z);

/**
 * @fn     complex_compare(complex_t *a, complex_t *b)
 * @author Romain Failla
 * @brief  Vérifie si a = b
 * @param  complex_t *a : l'adresse du premier nombre comparé
 * @param  complex_t *b : l'adresse du second nombre comparé
 * @return char : le résultat de la comparaison
 */
char complex_compare(complex_t *a, complex_t *b);

/**
 * @fn     complex_sum(complex_t *a, complex_t *b)
 * @author Romain Failla
 * @brief  Effectue a + b
 * @param  complex_t *a : l'adresse du premier terme de la somme
 * @param  complex_t *a : l'adresse du deuxième terme de la somme
 * @return complex_t* : l'adresse du résultat
 */
complex_t *complex_sum(complex_t *a, complex_t *b);

/**
 * @fn     complex_diff(complex_t *a, complex_t *b)
 * @author Romain Failla
 * @brief  Effectue a - b
 * @param  complex_t *a : l'adresse du premier terme de la différence
 * @param  complex_t *a : l'adresse du deuxième terme de la différence
 * @return complex_t* : l'adresse du résultat
 */
complex_t *complex_diff(complex_t *a, complex_t *b);

/**
 * @fn     complex_scalarProd(double k, complex_t *z)
 * @author Romain Failla
 * @brief  Réalise k * z
 * @param  double k : le scalaire du produit
 * @param  complex_t *z : le complexe du produit
 * @return complex_t* : l'adresse du résultat
 */
complex_t *complex_scalarProd(double k, complex_t *z);

/**
 * @fn     complex_prod(complex_t *a, complex_t *b)
 * @author Romain Failla
 * @brief  Effectue a * b
 * @param  complex_t *a : l'adresse du premier facteur du produit
 * @param  complex_t *a : l'adresse du deuxième terme du produit
 * @return complex_t* : l'adresse du résultat
 */
complex_t *complex_prod(complex_t *a, complex_t *b);

/**
 * @fn     complex_scalarDiv(complex_t *z, double k)
 * @author Romain Failla
 * @brief  Réalise z / k
 * @param  complex_t *z : le complexe du produit
 * @param  double k : le scalaire du produit
 * @return complex_t* : l'adresse du résultat
 */
complex_t *complex_scalarDiv(complex_t *z, double k);

/**
 * @fn     complex_div(complex_t *a, complex_t *b)
 * @author Romain Failla
 * @brief  Effectue a / b
 * @param  complex_t *a : l'adresse du premier facteur de la division
 * @param  complex_t *a : l'adresse du deuxième terme de la division
 * @return complex_t* : l'adresse du résultat
 */
complex_t *complex_div(complex_t *a, complex_t *b);

#endif
