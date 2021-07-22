/* organize words in document by number of occurences and
 * print each word followed by the line number of those
 * occurences in order */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	unsigned int count = 0;
	unsigned int* lines = NULL;
	char* data = NULL;
}word;

void crossref(unsigned int* table);

int main(int argc, char* argv[]) {

	return 0;
}
