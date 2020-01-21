#include "sorer.h"

int main(int argc, char** argv) {
	
	// 0) Check arguments
	
		// 1) read the file and calculate the number of cols and rows

	// 2) create a 2d array
	
	// 3) parse contents of the file
	
	char* str = readFile("data.sor", 0, 5);
	printf("str: %s\n", str);

	delete[] str;
	return 0;
}

