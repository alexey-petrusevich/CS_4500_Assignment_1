#include "sorer.h"

int main(int argc, char** argv) {
	
	// 0) Check arguments
	
		// 1) read the file and calculate the number of cols and rows

	// 2) create a 2d array
	
	// 3) parse contents of the file
	
	int* numCols = new int;
	char* str = readFile("data.sor", numCols);
	printf("str: %s\nnumCols: %d\n", str, *numCols);

	delete[] str;
	return 0;
}
