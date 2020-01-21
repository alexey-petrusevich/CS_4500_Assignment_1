//lang::CwC

#include <iostream>
#include <assert.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>

// reads a file from the file name and returns a pointer to a c-string
char* readFile(const char* filename, size_t from, size_t to) {
	assert(filename != nullptr);

	FILE* fp = fopen(filename, "r");

	if (fp == nullptr) {
		fprintf(stderr, "File: %s\nFailed to open the file.\n", filename);
		exit(1);
	}

	// move the file file pointer to the end of the fil
	fseek(fp, 0, SEEK_END);
	// get the size of the file
	size_t fileSize = static_cast<size_t>(ftell(fp));
	// move the file pointer back
	rewind(fp);

	long begin = 0;
	if (from > 0) {
		// loop through the file until the end of file or new line
		for (int c = fgetc(fp); c != EOF; fseek(fp, 1L, SEEK_CUR)) {
			printf("begin\n");
			if (c == '\n') {
				// tells the position of the file pointer
				begin = ftell(fp) + 1;
				break;
			}
		}
	}
	long end = fileSize;
	if (to < fileSize) {
		fseek(fp, to, SEEK_SET);
		long readPos = ftell(fp);
		printf("begin: %ld\n", begin);
		printf("read pos: %ld\n", readPos);
		printf("to: %zu\n", to);
		for (int c = fgetc(fp); readPos > begin; fseek(fp, -1L, SEEK_CUR)) {
			//printf("fp: %ld\n", ftell(fp));
			//printf("end\n");
			if (c == '\n') {
				end = ftell(fp);
				break;
			}
			readPos--;
		}
	}
	// move the file pointer to the begining of the file
	rewind(fp);

	// move file pointer to the specific position in the file
	fseek(fp, begin, SEEK_CUR);

	// create a buffer required for reading from the file
	size_t bufferSize = 255;
	char* buffer = new char[bufferSize];
	size_t memoryAdded = 0;

	size_t memoryLeftToRead = to - from;

	// the result string
	char* str = new char[bufferSize];
	//while(fscanf(fp, "%s", buffer) != EOF) {
	while (ftell(fp) < to) {
	//while(fgets(buffer, bufferSize, fp) != NULL) {
		// read a chunk of file to the buffer
		fgets(buffer, bufferSize, fp);
		// increment the memory added
		size_t bytesRead = strlen(buffer);
		memoryAdded += bytesRead;

		
		if (memoryLeftToRead < bufferSize) {
			// adjust the memory in the buffer
			memset(buffer + memoryLeftToRead, 0, bufferSize - memoryLeftToRead);
			//buffer[bufferSize + memoryLeftToRead - 1] = '\0';
		}
		

		memoryLeftToRead -= bytesRead;

		

		/*
		char* temp = new char[strlen(buffer) - 1];
		strncpy(temp, buffer, strlen(buffer) - 1);
		memset(buffer, 0, bufferSize);
		strcpy(buffer, temp);
		delete[] temp;
		*/

		// check if need more memory
		if (memoryAdded >= bufferSize) {	
			// double the size of the result string
			bufferSize *= 2;
			// create new memory of double the size
			char* temp = new char[bufferSize];
			// copy to the temp buffer
			strcpy(temp, str);
			// delete the origin string
			delete[] str;
			// reset the poiter of temp string to str
			str = temp;
		}

		// concatenate buffer to the result string
		strcat(str, buffer);
		// clear the memory of the buffer
		memset(buffer, 0, bufferSize);
	}
	// close the file
	fclose(fp);
	delete[] buffer;
	return str;
}


size_t getNumCols(const char* str) {
	
	return 0;
}

// populates the given array using values from string str
void populateArray(char** array, char* str, size_t numCols) {

}


// filters the array to have the same datatype per column
void filterArray(char** array, size_t numCols) {
	/*
	size_t counter = 0;
	...
	counter++;
	*/
}


// returns true if str is boolean and false otherwise
bool isBool(const char* str) {
	return true;	
}

bool isString(const char* str) {
	
	return true;	
}

bool isFloat(const char* str) {
	
	return true;	
}


bool isInteger(const char* str) {
	
	return true;	
}

// prints the type of the given column
void printColType(size_t col) {
	
}

// prints the value of the entry at the given col and row index
void printColIndex(size_t colIndex, size_t rowIndex) {
	
}

// prints if the given entry is missing a value
void isMissingIndex(size_t colIndex, size_t rowIndex) {
	
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
