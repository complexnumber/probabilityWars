#pragma once

#ifndef GeneralBuffer_hpp
#define GeneralBuffer_hpp

#include "ofMain.h"

template <class T>
class GeneralBuffer {
private:
	size_t len;
	T* arr;
	size_t allocated_length;
public:
	GeneralBuffer();
	GeneralBuffer(size_t length);
	void reset();
	void reset(size_t length);
	void clear();

	bool insertItemUniquely(T item);
	void insertItem(T item);

	T& operator[](unsigned int index);

	void reduceUniquely(T item);
	void reduceShiftList(unsigned int start_index);
	bool checkItem(T item);

	T* getArray();
	size_t length();
	size_t memory_length();
};

#endif /* GeneralBuffer.hpp */
