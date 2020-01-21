//lang::CwC

#include <assert.h>
#include <cstdio>
#include <cstring>

// prototypes

// reads a file, a pointer to number of rows, a pointer to numRows and numCols
// the latter two are used to calculate the number of row and columns
// while reading a file
// returns a pointer to the array of c-string pointers
// containing rows from the file
char* readFile(const char* filename, int* numCols) {
	assert(filename != nullptr);

	*numCols = 0;

	FILE* fp = fopen(filename, "r");
	size_t bufferSize = 255;
	char* buffer = new char[bufferSize];
	size_t memoryAdded = 0;
	
	char* str = new char[bufferSize];
	//while(fscanf(fp, "%s", buffer) != EOF) {
	while(fgets(buffer, bufferSize, fp) != NULL) {
		size_t bytesRead = strlen(buffer);
		memoryAdded += bytesRead;
		char* temp = new char[strlen(buffer) - 1];
		strncpy(temp, buffer, strlen(buffer) - 1);
		memset(buffer, 0, bufferSize);
		strcpy(buffer, temp);
		delete[] temp;
	//	printf("buffer: %s\n", buffer);
		// check if need more memory
		if (memoryAdded >= bufferSize) {	
			bufferSize *= 2;
			char* temp = str;
			str = new char[bufferSize];
			strcpy(str, temp);
			delete[] temp;
		}

		//printf("concatenating\n");
		strcat(str, buffer);
		if (bytesRead > *numCols) {
			*numCols = bytesRead;
		}
		memset(buffer, 0, bufferSize);
	}

	fclose(fp);
	delete[] buffer;
	return str;
}




// returns columns
char** getCols(const char* str);

// parses the column to a specific data type
// TODO add the type of the column at the head of the column
char* parseColumn(char* col);
/*
int main(int argc, char** argv) {
	
	// 0) Check arguments
	
	// 1) read the file and calculate the number of cols and rows

	// 2) create a 2d array
	
	// 3) parse contents of the file
	
	int* numCols = new int;
	char* str = readFile("data.sor", numCols);
	printf("numCols: %d\nstr: %s\n", *numCols, str);

	delete[] str;
	delete numCols;
	return 0;
}
*/
