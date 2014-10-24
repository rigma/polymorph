#ifndef CONSOLE_H
#define CONSOLE_H

#include <stdarg.h>

/**
 * @struct command_t
 * @author Romain Failla
 * @brief  Repr�sente une commande de la console
 */
typedef struct {
	char (*function)(const char *input);
	char *name;
} command_t;

/**
 * @struct console_t
 * @author Romain Failla
 * @brief  Repr�sente l'ensemble des commandes de la console
 */
typedef struct {
	command_t **commands;
	unsigned long size;
} console_t;

/**
 * @fn     console_init()
 * @author Romain Failla
 * @brief  Initialise une nouvelle console
 * @return console_t*
 */
console_t *console_init();

/**
 * @fn     console_free(console_t *console)
 * @author Romain Failla
 * @brief  Lib�re une console de la m�moire
 * @param  console_t *console : la console � lib�rer
 */
void console_free(console_t *console);

/**
 * @fn     console_run(console_t *console)
 * @author Romain Failla
 * @brief  Lance l'ex�cution d'une console
 * @param  console_t *console : l'adresse de la console � ex�cuter
 * @return int
 */
int console_run(console_t *console);

/**
 * @fn     console_appendCommand(console_t *console, const char *name, char (*function)(const char *input))
 * @author Romain Failla
 * @brief  Ajoute une nouvelle commande � la console
 * @param  console_t *console : l'adresse de la console cible
 * @param  const char *name : le nom de la commande
 * @param  char (*function)(const char *input) : l'adresse de la fonction de la nouvelle commande
 * @return char
 */
char console_appendCommand(console_t *console, const char *name, char (*function)(const char *input));

#endif
