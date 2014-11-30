#ifndef COMMANDS_H
#define COMMANDS_H

#include "buffer.h"
#include "manager.h"

/**
 * @fn     define(buffer_t *buffer, entry_t **list, const char *name)
 * @author Romain Failla | Etienne Quelain
 * @brief  D�fini un nouveau polyn�me en m�moire
 * @param  buffer_t *buffer : le buffer d'E/S
 * @param  entry_t **list : la liste des polyn�me d�fini en m�moire
 * @param  const char *name : le nom du polyn�me
 * @return int
 */
int define(buffer_t *buffer, entry_t **list, const char *name);

#endif
