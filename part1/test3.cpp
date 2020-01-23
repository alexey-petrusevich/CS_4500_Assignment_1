#include <iostream>
#include <cstring>

int main() {

	char* c = new char[10];
	strncpy(c, "hello", 0);

	printf("strlen: %zu\n", strlen(c));
	printf("c: %s\n", c);

	return 0;
}

