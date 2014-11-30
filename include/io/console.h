#ifndef CONSOLE_H
#define CONSOLE_H

#define DIFF   "diff"
#define INT    "int"
#define EXIT   "exit"
#define HELP   "help"
#define DEFINE "define"
#define EQUAL  "="
#define PLUS   "+"
#define MINUS  "-"
#define CROSS  "x"
#define DIVIDE "/"
#define MODULO "%"

/**
 * @enum   token_t
 * @author Romain Failla
 * @brief  Représente un mot clé de l'invité de commande
 */
typedef enum {
	TOK_DIFF = 10,
	TOK_INT = 9,
	TOK_EXIT = 8,
	TOK_HELP = 7,
	TOK_DEFINE = 6,
	TOK_EQUAL = 5,
	TOK_PLUS = 4,
	TOK_MINUS = 3,
	TOK_CROSS = 2,
	TOK_DIVIDE = 1,
	TOK_MODULO = 0,
	TOK_OTHER = -1
} token_t;

/**
 * @fn     getToken(char *str)
 * @author Romain Failla
 * @brief  Renvoie le token de la chaîne passé en argument
 * @param  char *str : la chaîne à tester
 * @return token_t
 */
token_t getToken(char *str);

/**
 * @fn     console_start(const char *msg)
 * @author Romain Failla
 * @brief  Lance l'invité de commande
 * @param  const char *msg : le message de l'invité de commande
 */
void console_start(const char *msg);

#endif
