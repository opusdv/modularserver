#include <stdio.h>


void* plugin_func(void* n) {
	int* num = (int*) n;
	printf("%d\n", *num);

	return n;
}
