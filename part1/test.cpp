#include <iostream>
#include <climits>
#include "sorer.h"


void testRead(size_t from, size_t to) {
	const char* filename = "data.sor";
	char* str = readFile(filename, from, to);
	printf("testReadAll: str: %s\n", str);
	delete[] str;
}

void testReadFileAll() 	{
	testRead(0, INT_MAX);
}

void testReadPastOne() {
	testRead(1, INT_MAX);
}

void testReadPastTwo() {
	testRead(2, INT_MAX);
};

int main() {
	testReadFileAll();
	testReadPastOne();
	testReadPastTwo();
	return 0;
}
