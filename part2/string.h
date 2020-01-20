//lang::CwC
#pragma once

#include "object.h"
#include <cstring>
#include <assert.h>

/**
 * @file string.h
 * @brief Implementation of String class.
 * @author Aliaksei Petrusevich
 * @date January 15, 2020
 */

/**
 * Represents sequence of characters.
 *
 * 
 * @author Aliaksei Petrusevich
 * @date January 15, 2020
 */
class String : public Object {
	public:
		char* str; // owned
		size_t size;
		
		/**
		 * The default constructor for this String class.
		 *
		 * @param str constant c-string value being stored in this String
		 */
		String(const char* str) : Object() {
			assert(str != nullptr);
			this->size = strlen(str);
			this->str = new char[this->size + 1];
			strcpy(this->str, str);
		}


		/**
		 * Construct a String from a c-string.
		 *
		 * @param str a c-string being used for creating new String
		 */
		String(char* str) : Object() {
			assert(str != nullptr);
			char* newStr = new char[strlen(str) + 1];
			strcpy(newStr, str);
			this->str = newStr;
			this->size = strlen(str);
		}


		/**
		 * Constructs a String from another String.
		 *
		 * @param str another String being used in constructing a new String
		 */
		String(String* str) : Object() {
			assert(str != nullptr);
			char* newString = new char[str->size + 1];
			strcpy(newString, str->str);
			this->str = newString;
			this->size = str->size;
		}


		/**
		 * Concatentates this string with another string and returns a result.
		 *
		 * @param otherString the given string
		 * @return the new string containing this string with concatenated
		 * given string
		 */
		String* concat(String* otherString) {
			assert(otherString != nullptr);
			// calculate new size
			size_t newSize = this->size + otherString->size + 1;
			// allocate new c-string
			char* newString = new char[newSize];
			// copy the value of this string minus \0 character
			strcpy(newString, this->str);
			// copy given string to the address of the remaining part of new string
			strcpy(newString + this->size, otherString->str);
			// create new instance of String
			String* str = new String(newString);
			delete[] newString;
			return str;
		}


		/**
		 * Returns the size of this String.
		 *
		 * @return the size of this String
		 */
		size_t length() {
			return this->size;
		}


		bool equals(Object* other) {
			assert(other != nullptr);
			// if casting failed, other cannot be cast to String
			String* otherStr = dynamic_cast<String*>(other);
			if (otherStr == nullptr) {
				return false;
			}
			return !strcmp(otherStr->str, this->str);
		}


		size_t hash() {
			int hash_ = 0;
			for (size_t i = 0; i < this->size; i++) {
				hash_ += this->str[i];
			}
			return hash_;
		}


		/**
		 * Returns an integer value  based on the lexicographical comaprison
		 * of this String to the given String. If the value is -1, 
		 * this String is lexicographically less than the given String.
		 * If the value is 1, this String is lexicographically greater
		 * than the given String. If return value is 0, Strings are equal.
		 *
		 * @param other the String this String is being compared against
		 * @return an integer result of comparing this String to the given String
		 */
		int compare_to(String* other) {
			assert(other != nullptr);
			return strcmp(this->str, other->str);	
		}


		/**
		 * The destructor for this String.
		 */
		~String() {
			delete this->str;
		}

};
