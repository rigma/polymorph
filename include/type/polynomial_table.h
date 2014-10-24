#ifndef POLYNOMIAL_TABLE
#define POLYNOMIAL_TABLE

#define POLYNOMIAL 0x0f
#define POLYMORPH  0xff

/**
 * @struct polynomial_table_entry_t
 * @author Romain Failla
 * @brief  Représente une entrée de la table de hachage polynomial_table_t
 */
typedef struct {
	void *polynomial;
	unsigned char type;
} polynomial_table_entry_t;

/**
 * @struct polynomial_table_t
 * @author Romain Failla
 * @brief  Représente une table de hachage de polynôme (développés ou factorisés) qui d'une taille fixe paramétrable
 */
typedef struct {
	polynomial_table_entry_t **polynomials;
	unsigned long size;     // Taille apparente
	unsigned long realSize; // Taille réelle
} polynomial_table_t;

/**
 * @fn     polynomial_table_init(unsigned long size)
 * @author Romain Failla
 * @brief  Initialise en mémoire une nouvelle table de hachage de polynôme
 * @param  La taille de la table de hachage
 * @return polynomial_table_t*
 */
polynomial_table_t *polynomial_table_init(unsigned long size);

/**
 * @fn     polynomial_table_free(polynomial_table_t *table)
 * @author Romain Failla
 * @brief  Libère la table de hachage de polynôme
 * @param  polynomial_table_t *table : la table de hachage
 */
void polynomial_table_free(polynomial_table_t *table);

/**
 * @fn     polynomial_table_hash(polynomial_table_t *table, const char *str)
 * @author Romain Failla librement inspiré par le projet DDDCPU16 de DeathlyDeep (https://github.com/DeathlyDeep/DDDCPU16)
 * @brief  Calcule l'entrée du polynôme avec un nom donnée dans la table de hachage
 * @param  polynomial_table_t *table : l'adresse de la table de hachage
 * @param  const char *str : le nom du polynôme
 * @return unsigned long
 */
unsigned long polynomial_table_hash(polynomial_table_t *table, const char *str);

/**
 * @fn     polynomial_table_get(polynomial_table_t *table, unsigned long hash)
 * @author Romain Failla
 * @brief  Renvoit le polynôme à l'entrée haché
 * @param  polynomial_table_t *table : la table de hachage
 * @param  unsigned long hash : la clé de hachage
 * @return polynomial_table_entry_t*
 */
polynomial_table_entry_t *polynomial_table_get(polynomial_table_t *table, unsigned long hash);

/**
 * @fn     polynomial_table_append(polynomial_table_t *table, void *polynomial, unsigned char type)
 * @author Romain Failla
 * @brief  Ajoute le polynôme polynomial dans la table de hachage
 * @param  polynomial_table_t *table : la table de hachage
 * @param  void *polynomial : l'adresse du polynôme
 * @param  unsigned char type : le type de polynôme
 * @return char
 */
char polynomial_table_append(polynomial_table_t *table, void *polynomial, unsigned char type);

/**
 * @fn     polynomial_table_remove(polynomial_table_t *table, const char *name)
 * @author Romain Failla
 * @brief  Enlève le polynôme d'après son nom de la table de hachage
 * @param  polynomial_table_t *table : la table de hachage
 * @param  const char *name : le nom du polynôme
 * @return char
 */
char polynomial_table_remove(polynomial_table_t *table, const char *name);

#endif
