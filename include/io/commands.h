#ifndef COMMANDS_H
#define COMMANDS_H

#include "buffer.h"
#include "manager.h"

/**
 * @fn     define(buffer_t *buffer, entry_t **list, char *args)
 * @author Romain Failla | Etienne Quelain
 * @brief  Défini un nouveau polynôme en mémoire
 * @param  buffer_t *buffer : le buffer d'E/S
 * @param  entry_t **list : la liste des polynômes définis en mémoire
 * @param  char *args : les arguments de la commande
 * @return int
 */
int define(buffer_t *buffer, entry_t **list, char *args);

/**
 * @fn      unset(entry_t **list, char *args)
 * @author  Romain Failla
 * @brief   Libère de la mémoire un polynôme enregistré
 * @param   entry_t **list : la liste des polynômes définis en mémoire
 * @param   char *args : les arguments de la commande
 * @return  int
 */
int unset(entry_t **list, char *args);

/**
 * @fn      display(entry_t *list, char *args)
 * @author  Romain Failla
 * @brief   Affiche le polynôme demandé
 * @param   entry_t *list : la liste des polynômes définis en mémoire
 * @param   char *args : les arguments de la commande
 * @return  int
 */
int display(entry_t *list, char *args);

/**
 * @fn      re(entry_t **list, char *args)
 * @author  Romain Failla
 * @brief   Affiche la partie réelle d'un polynôme donné et l'enregistre en mémoire
 * @param   entry_t **list : la liste des polynômes définis en mémoire
 * @param   char *args : les arguments de la commande
 * @return  int
 */
int re(entry_t **list, char *args);

/**
 * @fn      im(entry_t **list, char *args)
 * @author  Romain Failla
 * @brief   Affichae la partie imaginaire d'un polynôme donné
 * @param   entry_t **list : la liste des polynômes définis en mémoire
 * @param   char *args : les arguments de la commande
 * @return  int
 */
int im(entry_t **list, char *args);

/**
 * @fn      diff(entry_t **list, char *args)
 * @author  Romain Failla
 * @brief   Réalise, affiche et enregistre la dérivée d'un polynôme donné
 * @param   entry_t **list : la liste des polynômes définis en mémoire
 * @param   char *args : les arguments de la commande
 * @return  int
 */
int diff(entry_t **list, char *args);

/**
 * @fn      integrate(entry_t **list, char *args)
 * @author  Romain Failla
 * @brief   Réalise, affiche et enregistre la primitive d'un polynôme donné !
 * @param   entry_t **list : la liste des polynômes définis en mémoire
 * @param   char *args : les arguments de la commande
 * @return  int
 */
int integrate(entry_t **list, char *args);

#endif
