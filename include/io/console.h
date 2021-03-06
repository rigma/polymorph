#ifndef CONSOLE_H
#define CONSOLE_H

#define DIFF      "diff"
#define INTEGRATE "int"
#define RE        "re"
#define IM        "im"
#define EXIT      "exit"
#define HELP      "help"
#define DEFINE    "define"
#define UNSET     "unset"
#define DISPLAY   "display"
#define EQUAL     "="
#define PLUS      "+"
#define MINUS     "-"
#define CROSS     "x"
#define DIVIDE    "/"
#define MODULO    "%"

/**
 * @enum   token_t
 * @author Romain Failla
 * @brief  Repr�sente un mot cl� de l'invit� de commande
 */
typedef enum {
	TOK_DIFF = 14,
	TOK_INTEGRATE = 13,
	TOK_RE = 12,
	TOK_IM = 11,
	TOK_EXIT = 10,
	TOK_HELP = 9,
	TOK_DEFINE = 8,
	TOK_UNSET = 7,
	TOK_DISPLAY = 6,
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
 * @brief  Renvoie le token de la cha�ne pass� en argument
 * @param  char *str : la cha�ne � tester
 * @return token_t
 */
token_t getToken(char *str);

/**
 * @fn     console_start(const char *msg)
 * @author Romain Failla
 * @brief  Lance l'invit� de commande
 * @param  const char *msg : le message de l'invit� de commande
 */
void console_start(const char *msg);

#endif
