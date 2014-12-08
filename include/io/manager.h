#ifndef MANAGER_H
#define MANAGER_H

#include <type/polynomial.h>
#include <type/polymorph.h>

#define POLYNOMIAL 0x0
#define POLYMORPH  0x1

/**
 * @struct entry_t
 * @author Romain Failla
 * @brief  Repr�sente une entr�e du gestionnaire de polyn�me
 */
typedef struct entry_t {
	void *polynomial;
	unsigned char type;
	struct entry_t *next;
} entry_t;

/**
 * @fn     entry_free(entry_t **list)
 * @author Romain Failla
 * @brief  Lib�re toutes les entr�es de la liste des polyn�mes
 * @param  entry_t **list : la liste � lib�rer
 */
void entry_free(entry_t **list);

/**
 * @fn     entry_add(entry_t **list, void *polynomial, unsigned char type)
 * @author Romain Failla
 * @brief  Ajoute une nouvelle entr�e � la liste
 * @param  entry_t **list : la liste du gestionnaire
 * @param  void *polynomial : l'adresse du polyn�me � enregistrer
 * @param  unsigned char type : le type du polyn�me
 */
void entry_add(entry_t **list, void *polynomial, unsigned char type);

/**
 * @fn     entry_remove(entry_t **list, char *name)
 * @author Romain Failla
 * @brief  Enl�ve une entr�e de la liste en fonction du nom de polyn�me
 * @param  entry_t **list : la liste du gestionnaire
 * @param  char *name : le polyn�me � enlever
 */
void entry_remove(entry_t **list, char *name);

/**
 * @fn     entry_get(entry_t *list, char *name)
 * @author Romain Failla
 * @brief  Renvoie une entr�e de la liste en fonction du nom de polyn�me
 * @param  entry_t *list : la liste du gestionnaire
 * @param  char *name : le nom du polyn�me � r�cup�rer
 * @return entry_t*
 */
entry_t *entry_get(entry_t *list, char *name);

#endif
