#ifndef COMPLEX_H
#define COMPLEX_H

/**
 * @struct complex_t
 * @author Romain FAILLA
 * @brief  Repr�sente un nombre complexe en m�moire
 */
typedef struct {
	double re;  // la partie r�elle
	double im;  // la partie imaginaire
	double mod; // Le module du complexe
} complex_t;

/**
 * @fn     complex_init(double re, double im)
 * @author Romain Failla
 * @brief  Initialise en m�moire une structure complex_t
 * @param  double re : la partie r�elle du nouveau complexe
 * @param  double im : la partie imaginaire du nouveau complexe
 * @return complex_t* : l'adresse du nouveau complexe
 */
complex_t *complex_init(double re, double im);

/**
 * @fn     complex_free(complex_t *z)
 * @author Romain Failla
 * @brief  Lib�re de la m�moire une structure complex_t
 * @param  complex_t *z : l'adresse de la structure � lib�rer
 */
void complex_free(complex_t *z);

/**
 * @fn     complex_display(complex_t *z)
 * @brief  Renvoi une cha�ne de caract�re repr�sentant le nombre complexe
 * @author Romain Failla
 * @param  complex_t *z : l'adresse du nombre complexe � afficher
 * @param  unsigned int precision : la pr�cision de l'�criture (mettre � 0 pour la valeur par d�faut)
 * @return char*
 */
char *complex_display(complex_t *z, unsigned int precision);

/**
 * @fn     complex_conj(complex_t *z)
 * @brief  Renvoi l'adresse du conjugu� de z qui est allou� en m�moire
 * @author Romain Failla
 * @param  complex_t *z : l'adresse du nombre complexe trait�
 * @return complex_t* : l'adresse du conjugu�
 */
complex_t *complex_conj(complex_t *z);

/**
 * @fn     complex_compare(complex_t *a, complex_t *b)
 * @author Romain Failla
 * @brief  V�rifie si a = b
 * @param  complex_t *a : l'adresse du premier nombre compar�
 * @param  complex_t *b : l'adresse du second nombre compar�
 * @return char : le r�sultat de la comparaison
 */
char complex_compare(complex_t *a, complex_t *b);

/**
 * @fn     complex_sum(complex_t *a, complex_t *b)
 * @author Romain Failla
 * @brief  Effectue a + b
 * @param  complex_t *a : l'adresse du premier terme de la somme
 * @param  complex_t *a : l'adresse du deuxi�me terme de la somme
 * @return complex_t* : l'adresse du r�sultat
 */
complex_t *complex_sum(complex_t *a, complex_t *b);

/**
 * @fn     complex_diff(complex_t *a, complex_t *b)
 * @author Romain Failla
 * @brief  Effectue a - b
 * @param  complex_t *a : l'adresse du premier terme de la diff�rence
 * @param  complex_t *a : l'adresse du deuxi�me terme de la diff�rence
 * @return complex_t* : l'adresse du r�sultat
 */
complex_t *complex_diff(complex_t *a, complex_t *b);

/**
 * @fn     complex_scalarProd(double k, complex_t *z)
 * @author Romain Failla
 * @brief  R�alise k * z
 * @param  double k : le scalaire du produit
 * @param  complex_t *z : le complexe du produit
 * @return complex_t* : l'adresse du r�sultat
 */
complex_t *complex_scalarProd(double k, complex_t *z);

/**
 * @fn     complex_prod(complex_t *a, complex_t *b)
 * @author Romain Failla
 * @brief  Effectue a * b
 * @param  complex_t *a : l'adresse du premier facteur du produit
 * @param  complex_t *a : l'adresse du deuxi�me terme du produit
 * @return complex_t* : l'adresse du r�sultat
 */
complex_t *complex_prod(complex_t *a, complex_t *b);

/**
 * @fn     complex_scalarDiv(complex_t *z, double k)
 * @author Romain Failla
 * @brief  R�alise z / k
 * @param  complex_t *z : le complexe du produit
 * @param  double k : le scalaire du produit
 * @return complex_t* : l'adresse du r�sultat
 */
complex_t *complex_scalarDiv(complex_t *z, double k);

/**
 * @fn     complex_div(complex_t *a, complex_t *b)
 * @author Romain Failla
 * @brief  Effectue a / b
 * @param  complex_t *a : l'adresse du premier facteur de la division
 * @param  complex_t *a : l'adresse du deuxi�me terme de la division
 * @return complex_t* : l'adresse du r�sultat
 */
complex_t *complex_div(complex_t *a, complex_t *b);

#endif
