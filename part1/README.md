sorer.h 
    This file is where all our main helper code is running. This file is where we:
1) Read the file, parse through it, convert it to a usable string on which we will perform more activities (readFile and its helper functions)
2) Once the file has been converted to a string, we are calculating the number of columsn (longest line in the file) and number of rows ( the number of lines in the file)
3) these numbers help us calculate the size of our 2D array.
4) Our next step is to start parsing through the string and storing the characters contained within the <> into the array. Any empty spaces are stored with an empty string (generateArray). This step also ensures the string passes through several helper functions that ensure that the entry is a valid one based off the specs 
5) Once the array has been generated and stored in the 2D array, we filter through each column (filterArray). This step uses several helpers such as isBool, isInt, etc. which checks the most commonly occuring datatype in the column, and deletes all other types of data. This column hence now only has one datatype based on the most occuring. 
6) Now that the data is all prooperly stored, we have other methods such as printColtype, printColIndex and isMissingIndex which we can call straight from the terminal to find the correct information 

-----

data.sor
    This is the main file we are using to parse through, store into an array and filter through the array. It contains several 
    different examples of "bad data" and good data to parse through and store.

-----

main.cpp
    Main file that calls all the required helper code that is stored within sorer.h
    Runs the program 

------

Makefile
    Containing a set of directives used by a make build automation tool to generate a target/goal

-----

REPO.md 
    Contains the link to our Github repo on which we both have been working on 

-----
test.cpp
    A few different tests to help catch errors and ensure our code is running the way we want it to 
    
