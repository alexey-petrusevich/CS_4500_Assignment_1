//lang::CwC

#include <iostream>
#include <assert.h>
#include <cstdio>
#include <cstring>
#include <cstdlib>


// returns the size of the given file
size_t getFileSize(FILE* fp) {
	assert(fp != NULL);
	// move the file file pointer to the end of the fil
	fseek(fp, 0, SEEK_END);
	// get the size of the file
	size_t fileSize = static_cast<size_t>(ftell(fp));

	// move the file pointer back
	rewind(fp);
	return fileSize;
}


// returns the begin index given the file and the start index
// given by the user
// rewinds the file
long getBeginIndex(FILE* fp, size_t from) {
	assert(fp != NULL);
	// index of the next read position
	long beginIndex = 0;
	// if the file is not being read from the beginning
	// move the begin file pointer to the character following
	// the next line break
	if (from > 0) {
		// get the character at the current file index
		int c = fgetc(fp);
		while (c != '\n') {
			// move file pointer one position to the right
			fseek(fp, 1L, SEEK_CUR);
			// increment begin index
			beginIndex++;
			// get next character
			c = fgetc(fp);
		}
		// increment begin index so it points to the character after line break
		beginIndex++;
	}
	// move the file pointer to the begining of the file
	rewind(fp);

	return beginIndex;
}


// double the size of the given c-string given the size of the buffer
void doubleBuffer(char* buffer, size_t size) {
	assert(buffer != nullptr);
	size_t newBuffer = size * 2;
	char* temp = new char[newBuffer];
	strcpy(temp, buffer);
	delete[] buffer;
	buffer = temp;
}


// optimizes the length of the buffer - removes any unused space
char* optimizeLength(char* buffer) {
	assert(buffer != nullptr)
	size_t length = strlen(buffer);
	char* temp = new char[length + 1]; // 1 extra for \0 character
	strcpy(temp, buffer);
	delete[] buffer;
	return temp;
}


// returns the endIndex to be read from the file given
// the begin index and the to index specified by the user
// rewinds the file
long getEndIndex(FILE* fp, long beginIndex, size_t to) {
	assert(fp != nullptr);
	assert(static_cast<size_t>(beginIndex) < to);
	// TODO create helper function
	// index of the ending position
	long endIndex = getFileSize(fp) - 1;
	// if the 'to' position is less than the position of the filesize - 1
	if (to < endIndex) {
		// move the file 0 positions from the end
		fseek(fp, 0, SEEK_END);
		// get the character at the end of the file
		int c = fgetc(fp);
		// loop through the file until the new line character is foud
		while (c != '\n') {
			// move the file pointer one position to the left
			fseek(fp, -1L, SEEK_CUR);
			// decrement end index
			endIndex--;
			// check if read past the beginIndex
			if (endIndex <= beginIndex) {
				fprintf(stderr, "Invalid read parameters: endIndex <= beginIndex.\n");
				exit(1);
			}
			// get the next character
			c = fgetc(fp);
		}
		// decrement the
	}
	// move the file pointer to the begining of the file
	rewind(fp);

	return endIndex;
}


// reads the file from index to index given the file pointer,
// begin index and end index. the indices are already at the positions
// that skip lines (if neccessary)
char* readFileHelper(FILE* fp, long beginIndex, long endIndex) {	
	assert(fp != NULL);
	// check if begin index is greater or equal than end idnex
	if (beginIndex >= endIndex) {
		fprintf(stderr, "Error: begin index must be less than end index.\n");
		exit(1);
	}
	// move the file pointer to beginIndex from the begining of the file
	fseek(fp, beginIndex, SEEK_SET);

	// create a buffer required for reading from the file
	size_t bufferSize = 1024;
	char* buffer = new char[bufferSize];

	// the result string
	// initial size is the buffer size
	char* result = new char[bufferSize];

	size_t totalMemoryRead = 0; // keepts track of total memory read
	size_t resultSize = bufferSize; // keeps track of the result size

	// read the file using buffer from beginIndex to endIndex
	while (beginIndex < endIndex) {
		// read from the file into the buffer
		fgets(buffer, bufferSize, fp);
		size_t memoryRead = strlen(buffer);
		// increment totalMemoryRead by the number of bytes read
		// includes line break (\n) in count
		totalMemoryRead += memoryRead;
		// check if need to double the size of the result memory
		// if equals, there is not enough room for \0 character
		if (totalMemoryRead >= resultSize) {
			doubleBuffer(result, resultSize);
			resultSize *= 2;
		}
		// increment the begin index by memory read
		beginIndex += memoryRead;
		// copy buffer into result
		strcat(result, buffer);
	}
	// optimize length of the result of necessary
	result = optimizeLength(result);

	return result;
}



// reads a file from the file name and returns a pointer to a c-string
// if the from and to are not the beginning and the end index
// truncates the file to the nearest line breaks
char* readFile(const char* filename, size_t from, size_t to) {
	assert(filename != nullptr);
	// check if begin index is greater or equal than end idnex
	if (beginIndex >= endIndex) {
		fprintf(stderr, "Error: begin index must be less than end index.\n");
		exit(1);
	}

	FILE* fp = fopen(filename, "r");

	if (fp == nullptr) {
		fprintf(stderr, "File: %s\nFailed to open the file.\n", filename);
		exit(1);
	}

	size_t filesize = getFileSize(fp);

	// check if to index is greater than the filesize
	// if true, set to the filesize
	if (to > filesize - 1) {
		to = filesize - 1;
	}

	long beginIndex = getBeginIndex(fp, from);
	long endIndex = getEndIndex(fp, beginIndex, to);

	char* str = readFileHelper(fp, beginIndex, endIndex);

	fclose(fp);
	return str;
}


// TODO Alex
// generates an array of strings representing a table with values
// populates the given array using values from string str
// remove brakets from entries
char** generateArray(char* str) {
	assert(str != nullptr);

	// get the number of columns and rows
	size_t numCols = getNumCols(str);
	size_t numRows = getNumRows(str);
	char** cols = new char*[numCols];
		
	// get the longest line in the given string to determine
	// the size of the buffer
	size_t bufferSize = longestLine(str);
	size_t buffer = new char[bufferSize + 1]; // 1 for \0
	
	// get the pointer to the next row
	char* nextRowPtr = getRowPtr(str);


	for (size_t colIndex = 0; colIndex < numCols; colIndex++) {
		// create new column as big as the number of rows
		cols[colIndex] = new char[numRows];
		for (size_t rowIndex = 0; rowIndex < numRows; rowIndex++) {
			// copy row and get all the entries in that row
			// TODO create hasNextEntryMethod
			// TODO complete implementation
		}
	}

	// read each line until the end of the file
		


	return cols;
}

// returns a pointer to the next row in the given string
// returns nullptr if no more rows found
char* nextRowPtr(char* str) {
	char* nextRow = str;
	while(nextRow != '\n') {
		if (nextRow == '\0') {
			return nullptr;
		}
		nextRow += 1;
	}
	return nextRow;
}

// returns the longest sequence of characters in the given c-string
size_t longestLine(char* str) {
	assert(str != nullptr);
	size_t max = 0;
	size_t currentMax = 0;
	size_t i = 0;
	while (str[i] != '\0') {
		// when reached new line and if current max counter is greater than max
		if (str[i] == '\n' && currentMax > max) {
			// reset max
			max = currentMax;
			currentMax = 0;
		} else {
			currentMax++;
		}
	}
	return max + 1; // 1 for new line character
}


// returns the number of rows in a string
size_t numRows(char* str) {
	assert(str != nullptr);
	size_t numRows = 0;
	size_t i = 0;
	while (str[i] != '\0') {
		if (str[i] == '\n') {
			numRows++;
		}
		i++;
	}
	return numRows;
}

// returns a copy of the next entry
// removes angle brackets
// caller is responsible for freeing the memory
char* getNextEntry(char* str) {
	size_t entryLength = 0; // length of the entry to be created
	size_t beginValidIndex = 0; // holds
	// get the pointer to the next entry
	char* nextEntryPtr = nextEntryPtr(str);
	// if nextEntryPtr is nullptr, there are no more entries to read; EOF
	if (nextEntryPtr == nullptr) {
		return nullptr;
	}
	// holds the end index of a valid entry
	size_t endValidIndex = 0;
	// skip any preceeding spaces
	skipSpaces(nextEntryPtr, &beginValidIndex);
	// check validity of the middle
	if (isValid(nextEntryPtr, &lastValidIndex)) {
		// create a copy of the valid string and return
		char* result = new char[lastValidIndex - beginValidIndex];
		return result;
	} else {
		return "";
		/* maybe exit??????
		// entry is invalid
		fprintf(stderr, "Malformed entry found.\n");
		exit(2);
		*/
	}
}


// skips spaces given the string and the index
// increments index
void skipSpaces(char* str, size_t* i) {
	assert(str != nullptr);
	assert(i != nullptr);
	while(str[*i] == ' ') {
		(*i)++;
	}
}


// returns true if the given sequence of characters is a valid entry until
// the next space or the angle bracket
// assumes no escape sequences
// str is guaranteed to begin with the actual entry (not < or spaces after <)
bool isValidEntry(char* str, size_t* endValidIndex) {
	assert(str != nullptr);
	assert(endValidIndex != nullptr);
	*endValidIndex = 0;
	bool qFlag = false;
	bool foundSpace = false;
	// loop until the end of the entry
	while(str[i] != '>') {
		if (str[i] == '\0') {
			// end of file, malformed
			return false;
		}
		if (str[i] != ' ') {
			// if non-space character but encountered a space already (no quotes)
			if (foundSpace) {
				// space found in the entry without quotes, malformed entry
				return false;
			}
		} else if (str[0] != '"')  { 
			// else character is a space and not within quoted string
			foundSpace = true;
		}
		// else character is whether is quotes or a valid part of the entry
		(*endValidIndex)++;
	}
	// if here, entry is valid
	return true;
}


// a helper function for getNext entry that returns a pointer to the next
// entry in the given string
char* nextEntryPtr(char* str) {
	assert(str != nullptr);
	size_t i = 0;
	while (str != '\0') {
		if (str[i] == '<') {
			return str + i;
		}
		i++;
	}
	// return nullptr if no more entries found
	return nullptr;
}


// TODO Alex
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
	if (strcmp(str, "0")|| strcmp(str, "1")) {
		return true;
	}
	return false;
}

// returns true if str is integer and false otherwise
bool isInteger(const char* str) {
	// finds and stores the length of the str 
	size_t length = sizeof(str);

	// to check if the first item in the str is a + or - to represent the integer
	int plusOrMinus = static_cast<int>(str[0]);
	//compares against ASCII values
	if(plusOrMinus == 043 || plusOrMinus == 045) {
		// do nothing 
	}

	for(int i = 1; i< length; i++) {
		int intConverted = static_cast<int>(str[i]);
		if(isdigit(intConverted) == 0) { return false;}
	}	
	return true;
}

// returns true if str is float and false otherwise
bool isFloat(const char* str) {
	// finds and stores the length of the str 
	size_t length = sizeof(str);
	//counter to check how many times the point occurs in float
	int periodCounter = 0;

	// to check if the first item in the str is a + or - to represent the integer/float
	int plusOrMinus = static_cast<int>(str[0]);
	//compares against ASCII values
	if(plusOrMinus == 043 || plusOrMinus == 045) {
		// do nothing 
	}

	for(int i = 1; i< length; i++) {
		int intConverted = static_cast<int>(str[i]);
		//if more than one period occurs, it is not a valid float value
		if(periodCounter > 1) {
			return false;
		}
		//compares against ASCII value
		if(intConverted == 046) {
			periodCounter++;
		}
		if(isdigit(intConverted) == 0) { return false;}
	}	
	return true;
}

// returns true if str is string and false otherwise
bool isString(const char* str) {
	if((isBool(str)!= 1) && 
	   (isFloat(str)!= 1) &&
	   (isInteger(str))!= 1) {
			return true;
		}
	return false;	
}

// TODO Alex
// prints the type of the given column
void printColType(size_t col) {
	
}

// TODO Alex
// prints the value of the entry at the given col and row index
void printColIndex(size_t colIndex, size_t rowIndex) {
	
}

// TODO Alex
// prints if the given entry is missing a value
void isMissingIndex(size_t colIndex, size_t rowIndex) {
	
}

