#pragma once

#ifndef GeneralBuffer_hpp
#define GeneralBuffer_hpp

#include "ofMain.h"

template <class T>
class GeneralBuffer {
private:
	size_t len; // Length of the actively used memory
	T* arr; // Pointer for the buffer
	size_t allocated_length; // Length of the allocated memory
public:
	GeneralBuffer(); // Constructor with no allocation
	GeneralBuffer(size_t length); // Constructor with allocation
	void reset(); // Destroys buffer
	void reset(size_t length); // Destroys buffer, then allocates memory
	void clear(); // Resets actively used memory

	bool insertItemUniquely(T item); // If item exists, insertion does not occurs, if not, item is inserted from the end
	void insertItem(T item); // Inserts without check of existence

	T& operator[](unsigned int index); // Overloads [] operator

	void reduceUniquely(T item); // Finds the item, then shifts the list leftwards from the item's position
	T reduceShiftList(unsigned int start_index); // Shifts the list leftwards from the index
	bool checkItem(T item); // Check existence of the item

	T* getBuffer();
	size_t length();
	size_t memory_length();
};

#endif /* GeneralBuffer.hpp */
