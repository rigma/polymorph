#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <io/buffer.h>
#include <io/console.h>

token_t getToken(const char *str)
{
	if (!strcmp(str, EXIT))
		return TOK_EXIT;
	else if (!strcmp(str, HELP))
		return TOK_HELP;
	else if (!strcmp(str, DEFINE))
		return TOK_DEFINE;
	else if (!strcmp(str, EQUAL))
		return TOK_EQUAL;
	else if (!strcmp(str, PLUS))
		return TOK_PLUS;
	else if (!strcmp(str, MINUS))
		return TOK_MINUS;
	else if (!strcmp(str, CROSS) || !strcmp(str, "*"))
		return TOK_CROSS;
	else if (!strcmp(str, DIVIDE))
		return TOK_DIVIDE;
	else if (!strcmp(str, MODULO))
		return TOK_MODULO;
	else
		return TOK_OTHER;
}

void console_start(const char *msg)
{
	FILE *f = NULL;
	buffer_t *buffer = NULL;
	char *str = NULL;
	char run = 0, c = 0;

	f = fopen(msg, "r");
	if (f == NULL)
		printf("ERREUR : impossible de charger le message de bienvenue !\nLancement du terminal...\n\n\n");
	else
	{
		do
		{
			c = fgetc(f);
			fputc(c, stdout);
		} while (c != EOF);

		fclose(f);
		f = NULL;

		printf("\n\n");
	}

	buffer = buffer_init(0);
	if (buffer == NULL)
	{
		printf("ERREUR : impossible d'initialiser le buffer d'E/S ! Fermeture de l'application.\n");
		exit(EXIT_FAILURE);
	}

	run = 1;
	while (run)
	{
		buffer_read(buffer, 0, ">> ");
		str = buffer_get(buffer);

		switch (getToken(str))
		{
		case TOK_EXIT:
			run = 0;
			break;

		case TOK_HELP:
			printf("%s\n", str);
			break;

		default:
			printf("YOLO !\n");
		}

		free(str);
	}

	buffer_free(buffer);
}
