#ifndef COMMANDS_H
#define COMMANDS_H

#include "buffer.h"
#include "manager.h"

/**
 * @fn     define(buffer_t *buffer, entry_t **list, char *args)
 * @author Romain Failla | Etienne Quelain
 * @brief  D�fini un nouveau polyn�me en m�moire
 * @param  buffer_t *buffer : le buffer d'E/S
 * @param  entry_t **list : la liste des polyn�mes d�finis en m�moire
 * @param  char *args : les arguments de la commande
 * @return int
 */
int define(buffer_t *buffer, entry_t **list, char *args);

/**
 * @fn      display(entry_t *list, char *args)
 * @author  Romain Failla
 * @brief   Affiche le polyn�me demand�
 * @param   entry_t *list : la liste des polyn�mes d�finis en m�moire
 * @param   char *args : les arguments de la commande
 * @return  int
 */
int display(entry_t *list, char *args);

/**
 * @fn      diff(entry_t **list, char *args)
 * @author  Romain Failla
 * @brief   R�alise, affiche et enregistre la d�riv�e d'un polyn�me donn�
 * @param   entry_t **list : la liste des polyn�mes d�finis en m�moire
 * @param   char *args : les arguments de la commande
 * @return  int
 */
int diff(entry_t **list, char *args);

/**
 * @fn      integrate(entry_t **list, char *args)
 * @author  Romain Failla
 * @brief   R�alise, affiche et enregistre la primitive d'un polyn�me donn� !
 * @param   entry_t **list : la liste des polyn�mes d�finis en m�moire
 * @param   char *args : les arguments de la commande
 * @return  int
 */
int integrate(entry_t **list, char *args);

#endif
