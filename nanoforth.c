#include "config.h"
#ifndef ARDUINO
#include "platform.h"
#include "stack.h"
#include "forth.h"
#include <string.h>

#define BUFFER_SIZE 100
int main(int argc, char* argv[]) {
	printf("? ");

	char buffer[BUFFER_SIZE];
	while (fgets(buffer, BUFFER_SIZE, stdin) != NULL) {
		printf("read: %s\n", buffer);
		inputString = _strdup(buffer);
		repl();
	}
}
#endif
