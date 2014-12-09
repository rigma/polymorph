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
	else if (!strcmp(table[0], EXIT) || !strcmp(table[0], "bye") || !strcmp(table[0], "quit"))
		result = TOK_EXIT;
	else if (!strcmp(table[0], HELP))
		result = TOK_HELP;
	else if (!strcmp(table[0], DEFINE) || !strcmp(table[0], "set"))
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
	char *input = NULL;
	char run = 0, code = 0, c = 0;

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

		fprintf(stdout, "\n\n");
	}

	buffer = buffer_init(0);
	if (buffer == NULL)
	{
		fprintf(stdout, "ERREUR : impossible d'initialiser le buffer d'E/S ! Fermeture de l'application.\n");
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
			code = diff(&polynomials, input);
			break;

		case TOK_INTEGRATE:
			code = integrate(&polynomials, input);
			break;

		case TOK_RE:
			code = re(&polynomials, input);
			break;

		case TOK_IM:
			code = im(&polynomials, input);
			break;

		case TOK_EXIT:
			run = 0;
			break;

		case TOK_HELP:
			f = fopen(msg, "r");
			if (f == NULL)
				fprintf(stdout, "L'aide n'est pas disponible...\n");
			else
			{
				do
				{
					c = fgetc(f);
					fputc(c, stdout);
				} while (c != EOF);

				fclose(f);
				f = NULL;

				fprintf(stdout, "\n");
			}
			break;

		case TOK_DISPLAY:
			code = display(polynomials, input);
			break;

		case TOK_DEFINE:
			code = define(buffer, &polynomials, input);
			break;
			
		case TOK_UNSET:
			code = unset(&polynomials, input);
			break;

		default:
			code = expr(&polynomials, input);
		}

		if (code == EXIT_FAILURE && run)
			printf("Erreur ! La commande ne s'est executee correctement.\n");
	}

	entry_free(&polynomials);
	buffer_free(buffer);
}
