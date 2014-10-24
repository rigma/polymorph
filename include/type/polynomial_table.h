#ifndef POLYNOMIAL_TABLE
#define POLYNOMIAL_TABLE

#define POLYNOMIAL 0x0f
#define POLYMORPH  0xff

/**
 * @struct polynomial_table_entry_t
 * @author Romain Failla
 * @brief  Repr�sente une entr�e de la table de hachage polynomial_table_t
 */
typedef struct {
	void *polynomial;
	unsigned char type;
} polynomial_table_entry_t;

/**
 * @struct polynomial_table_t
 * @author Romain Failla
 * @brief  Repr�sente une table de hachage de polyn�me (d�velopp�s ou factoris�s) qui d'une taille fixe param�trable
 */
typedef struct {
	polynomial_table_entry_t **polynomials;
	unsigned long size;     // Taille apparente
	unsigned long realSize; // Taille r�elle
} polynomial_table_t;

/**
 * @fn     polynomial_table_init(unsigned long size)
 * @author Romain Failla
 * @brief  Initialise en m�moire une nouvelle table de hachage de polyn�me
 * @param  La taille de la table de hachage
 * @return polynomial_table_t*
 */
polynomial_table_t *polynomial_table_init(unsigned long size);

/**
 * @fn     polynomial_table_free(polynomial_table_t *table)
 * @author Romain Failla
 * @brief  Lib�re la table de hachage de polyn�me
 * @param  polynomial_table_t *table : la table de hachage
 */
void polynomial_table_free(polynomial_table_t *table);

/**
 * @fn     polynomial_table_hash(polynomial_table_t *table, const char *str)
 * @author Romain Failla librement inspir� par le projet DDDCPU16 de DeathlyDeep (https://github.com/DeathlyDeep/DDDCPU16)
 * @brief  Calcule l'entr�e du polyn�me avec un nom donn�e dans la table de hachage
 * @param  polynomial_table_t *table : l'adresse de la table de hachage
 * @param  const char *str : le nom du polyn�me
 * @return unsigned long
 */
unsigned long polynomial_table_hash(polynomial_table_t *table, const char *str);

/**
 * @fn     polynomial_table_get(polynomial_table_t *table, unsigned long hash)
 * @author Romain Failla
 * @brief  Renvoit le polyn�me � l'entr�e hach�
 * @param  polynomial_table_t *table : la table de hachage
 * @param  unsigned long hash : la cl� de hachage
 * @return polynomial_table_entry_t*
 */
polynomial_table_entry_t *polynomial_table_get(polynomial_table_t *table, unsigned long hash);

/**
 * @fn     polynomial_table_append(polynomial_table_t *table, void *polynomial, unsigned char type)
 * @author Romain Failla
 * @brief  Ajoute le polyn�me polynomial dans la table de hachage
 * @param  polynomial_table_t *table : la table de hachage
 * @param  void *polynomial : l'adresse du polyn�me
 * @param  unsigned char type : le type de polyn�me
 * @return char
 */
char polynomial_table_append(polynomial_table_t *table, void *polynomial, unsigned char type);

/**
 * @fn     polynomial_table_remove(polynomial_table_t *table, const char *name)
 * @author Romain Failla
 * @brief  Enl�ve le polyn�me d'apr�s son nom de la table de hachage
 * @param  polynomial_table_t *table : la table de hachage
 * @param  const char *name : le nom du polyn�me
 * @return char
 */
char polynomial_table_remove(polynomial_table_t *table, const char *name);

#endif
