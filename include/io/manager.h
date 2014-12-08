#ifndef MANAGER_H
#define MANAGER_H

#include <type/polynomial.h>
#include <type/polymorph.h>

#define POLYNOMIAL 0x0
#define POLYMORPH  0x1

/**
 * @struct entry_t
 * @author Romain Failla
 * @brief  Représente une entrée du gestionnaire de polynôme
 */
typedef struct entry_t {
	void *polynomial;
	unsigned char type;
	struct entry_t *next;
} entry_t;

/**
 * @fn     entry_free(entry_t **list)
 * @author Romain Failla
 * @brief  Libère toutes les entrées de la liste des polynômes
 * @param  entry_t **list : la liste à libérer
 */
void entry_free(entry_t **list);

/**
 * @fn     entry_add(entry_t **list, void *polynomial, unsigned char type)
 * @author Romain Failla
 * @brief  Ajoute une nouvelle entrée à la liste
 * @param  entry_t **list : la liste du gestionnaire
 * @param  void *polynomial : l'adresse du polynôme à enregistrer
 * @param  unsigned char type : le type du polynôme
 */
void entry_add(entry_t **list, void *polynomial, unsigned char type);

/**
 * @fn     entry_remove(entry_t **list, char *name)
 * @author Romain Failla
 * @brief  Enlève une entrée de la liste en fonction du nom de polynôme
 * @param  entry_t **list : la liste du gestionnaire
 * @param  char *name : le polynôme à enlever
 */
void entry_remove(entry_t **list, char *name);

/**
 * @fn     entry_get(entry_t *list, char *name)
 * @author Romain Failla
 * @brief  Renvoie une entrée de la liste en fonction du nom de polynôme
 * @param  entry_t *list : la liste du gestionnaire
 * @param  char *name : le nom du polynôme à récupérer
 * @return entry_t*
 */
entry_t *entry_get(entry_t *list, char *name);

#endif
