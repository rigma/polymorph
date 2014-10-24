#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <io/buffer.h>
#include <io/console.h>

console_t *console_init()
{
	console_t *console = (console_t*) malloc(sizeof(console_t));
	if (console == NULL)
		return NULL;

	console->commands = NULL;
	console->size = 0;

	return console;
}

void console_free(console_t *console)
{
	unsigned long i = 0;

	if (console == NULL)
		return;

	for (i = 0 ; i < console->size ; i++)
	{
		free(console->commands[i]->name);
		free(console->commands[i]);
	}

	free(console);
}

int console_run(console_t *console)
{
	buffer_t *buffer = NULL;
	char *input = NULL;
	char run = 1;

	if (console == NULL)
		return EXIT_FAILURE;

	buffer = buffer_init(0);
	if (buffer == NULL)
		return EXIT_FAILURE;

	while (run)
	{
		buffer_read(buffer, 0, "> ");

		input = buffer_get(buffer);

		if (!strcmp(input, "hello"))
			printf("Hello world !\n");
		else if (!strcmp(input, "exit") || !strcmp(input, "bye"))
			run = 0;
	}

	buffer_free(buffer);
	
	return EXIT_SUCCESS;
}

char console_appendCommand(console_t *console, const char *name, char (*function)(const char *input))
{
	command_t *command = NULL;

	if (console == NULL || name == NULL || function == NULL)
		return 0;

	command = (command_t*) malloc(sizeof(command_t));
	if (command == NULL)
		return 0;

	command->name = (char*) malloc(sizeof(name) * sizeof(char));
	if (command->name == NULL)
	{
		free(command);

		return 0;
	}

	strcpy(command->name, name);

	command->function = function;

	return 1;
}
