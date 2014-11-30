#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <io/buffer.h>
#include <io/console.h>
#include <io/commands.h>

token_t getToken(char *str)
{
	char *input = strtok(str, " ");
	token_t result = TOK_OTHER;

	if (!strcmp(input, DIFF))
		result = TOK_DIFF;
	else if (!strcmp(input, INT))
		result = TOK_INT;
	else if (!strcmp(input, EXIT))
		result = TOK_EXIT;
	else if (!strcmp(input, HELP))
		result = TOK_HELP;
	else if (!strcmp(input, DEFINE))
		result = TOK_DEFINE;

	return result;
}

void console_start(const char *msg)
{
	FILE *f = NULL;
	buffer_t *buffer = NULL;
	entry_t *polynomials = NULL;
	char *input = NULL, *str = NULL;
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
		
		str = (char*) malloc(sizeof(input) * sizeof(char));
		strcpy(str, input);

		switch (getToken(str))
		{
		case TOK_EXIT:
			run = 0;
			break;

		case TOK_HELP:
			printf("%s\n", input);
			break;

		case TOK_DEFINE:
			free(input);
			
			input = strtok(NULL, " ");
			define(buffer, &polynomials, input);
			break;

		default:
			printf("YOLO !\n");
		}
	}

	buffer_free(buffer);
}
