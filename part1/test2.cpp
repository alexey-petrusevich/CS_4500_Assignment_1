#include <iostream>
#include <cstring>
#include "sorer.h"

int main() {


	char* str = readFile("test2.txt", 0, 1000);

	printf("strlen: %zu\n", strlen(str));

	printf("str123456: %s\n", str);

	return 0;
}
