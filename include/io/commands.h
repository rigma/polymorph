#ifndef COMMANDS_H
#define COMMANDS_H

#include "buffer.h"
#include "manager.h"

/**
 * @fn     define(buffer_t *buffer, entry_t **list, const char *name)
 * @author Romain Failla | Etienne Quelain
 * @brief  Défini un nouveau polynôme en mémoire
 * @param  buffer_t *buffer : le buffer d'E/S
 * @param  entry_t **list : la liste des polynôme défini en mémoire
 * @param  const char *name : le nom du polynôme
 * @return int
 */
int define(buffer_t *buffer, entry_t **list, const char *name);

#endif
