#ifndef BUFFER_H
#define BUFFER_H

#define HISTORY 256

#include <stdlib.h>

/**
 * @struct buffer_t
 * @author Romain Faill
 * @brief  Représente un tampon d'E/S via stdin
 */
typedef struct {
	size_t size;
	char **buffer;
} buffer_t;

/**
 * @fn     buffer_init(size_t offset)
 * @author Romain Failla
 * @brief  Initialise un tampon d'E/S via stdin
 * @param  size_t offset : demande à la fonction d'allouer un certain nombre de case en mémoire à l'initialisation
 * @return buffer_t*
 */
buffer_t *buffer_init(size_t offset);

/**
 * @fn     buffer_free(buffer_t *buffer)
 * @author Romain Failla
 * @brief  Libère le tampon un tampon d'E/S via stdin
 * @param  buffer_t *buffer : le tampon à libérer
 */
void buffer_free(buffer_t *b);

/**
 * @fn     buffer_read(buffer_t *b, size_t lenght, const char *prefix)
 * @author Romain Failla
 * @brief  Lit une chaîne de caractère d'une taille donnée depuis stdin ('\n' n'est pris en compte que lorsque lenght = 0)
 * @param  buffer_t *b : le tampon E/S
 * @param  size_t lenght : la taille de la chaîne à lire (s'il vaut 0, on lit jusqu'à ce qu'on recoive '\n')
 * @param  const char *prefix : ajoute une petite sortie avant la saisie
 * @return char
 */
char buffer_read(buffer_t *b, size_t lenght, const char *prefix);

/**
 * @fn     buffer_get(buffer_t *b)
 * @author Romain Failla
 * @brief  Récupère une chaîne de caractères depuis le tampon
 * @param  buffer_t *b : le tampon E/S
 * @return char*
 */
char *buffer_get(buffer_t *b);

#endif
