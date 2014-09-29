#include <stdlib.h>
#include <stdio.h>

#include <io/buffer.h>

int main(int argc, char **argv)
{
	char *str = (char*) NULL;
	buffer_t *buffer = buffer_init(0);

	buffer_read(buffer, 0, "Saississez un mot : ");
	buffer_read(buffer, 0, "Saississez encore un mot : ");

	str = buffer_get(buffer);
	printf("Vous avez saisi : %s\n", str);
	free(str);

	str = buffer_get(buffer);
	printf("Ensuite, vous avez saisi : %s\n", str);

	buffer_free(buffer);
	free(str);

	system("pause");

	return EXIT_SUCCESS;
}
