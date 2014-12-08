#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <io/buffer.h>
#include <io/console.h>
#include <io/commands.h>
#include <utils.h>

token_t getToken(char *str)
{
	char **table = NULL;
	size_t i = 0, size = 0;
	token_t result = TOK_OTHER;

	table = split(str, ' ', &size);

	if (!strcmp(table[0], DIFF))
		result = TOK_DIFF;
	else if (!strcmp(table[0], INTEGRATE))
		result = TOK_INTEGRATE;
	else if (!strcmp(table[0], RE))
		result = TOK_RE;
	else if (!strcmp(table[0], IM))
		result = TOK_IM;
	else if (!strcmp(table[0], EXIT))
		result = TOK_EXIT;
	else if (!strcmp(table[0], HELP))
		result = TOK_HELP;
	else if (!strcmp(table[0], DEFINE))
		result = TOK_DEFINE;
	else if (!strcmp(table[0], UNSET))
		result = TOK_UNSET;
	else if (!strcmp(table[0], DISPLAY))
		result = TOK_DISPLAY;

	for (i = 0; i < size; i++)
		free(table[i]);

	free(table);

	return result;
}

void console_start(const char *msg)
{
	FILE *f = NULL;
	buffer_t *buffer = NULL;
	entry_t *polynomials = NULL;
	char **table = NULL, *input = NULL;
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
		input = buffer_get(buffer);

		switch (getToken(input))
		{
		case TOK_DIFF:
			diff(&polynomials, input);
			break;

		case TOK_INTEGRATE:
			integrate(&polynomials, input);
			break;

		case TOK_RE:
			re(&polynomials, input);
			break;

		case TOK_IM:
			im(&polynomials, input);
			break;

		case TOK_EXIT:
			run = 0;
			break;

		case TOK_HELP:
			printf("%s\n", input);
			break;

		case TOK_DISPLAY:
			display(polynomials, input);
			break;

		case TOK_DEFINE:
			define(buffer, &polynomials, input);
			break;
			
		case TOK_UNSET:
			unset(&polynomials, input);
			break;

		default:
			printf("YOLO !\n");
		}
	}

	entry_free(&polynomials);
	buffer_free(buffer);
}
