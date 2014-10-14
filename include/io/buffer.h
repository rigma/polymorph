#ifndef BUFFER_H
#define BUFFER_H

#define HISTORY 256

#include <stdlib.h>

/**
 * @struct buffer_t
 * @author Romain Faill
 * @brief  Repr�sente un tampon d'E/S via stdin
 */
typedef struct {
	size_t size;
	char **buffer;
} buffer_t;

/**
 * @fn     buffer_init(size_t offset)
 * @author Romain Failla
 * @brief  Initialise un tampon d'E/S via stdin
 * @param  size_t offset : demande � la fonction d'allouer un certain nombre de case en m�moire � l'initialisation
 * @return buffer_t*
 */
buffer_t *buffer_init(size_t offset);

/**
 * @fn     buffer_free(buffer_t *buffer)
 * @author Romain Failla
 * @brief  Lib�re le tampon un tampon d'E/S via stdin
 * @param  buffer_t *buffer : le tampon � lib�rer
 */
void buffer_free(buffer_t *b);

/**
 * @fn     buffer_read(buffer_t *b, size_t lenght, const char *prefix)
 * @author Romain Failla
 * @brief  Lit une cha�ne de caract�re d'une taille donn�e depuis stdin ('\n' n'est pris en compte que lorsque lenght = 0)
 * @param  buffer_t *b : le tampon E/S
 * @param  size_t lenght : la taille de la cha�ne � lire (s'il vaut 0, on lit jusqu'� ce qu'on recoive '\n')
 * @param  const char *prefix : ajoute une petite sortie avant la saisie
 * @return char
 */
char buffer_read(buffer_t *b, size_t lenght, const char *prefix);

/**
 * @fn     buffer_get(buffer_t *b)
 * @author Romain Failla
 * @brief  R�cup�re une cha�ne de caract�res depuis le tampon
 * @param  buffer_t *b : le tampon E/S
 * @return char*
 */
char *buffer_get(buffer_t *b);

#endif
