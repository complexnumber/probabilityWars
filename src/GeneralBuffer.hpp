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

	bool insertItemUniquely(T item);
	T getItem(unsigned int& index);
	void insertItem(T item);
	void setItem(unsigned int& index, T item);
	T* getArray();

	void reduceShiftList(unsigned int start_index);
	bool checkItem(T item);
	size_t length();
	size_t memory_length();
};

#endif /* GeneralBuffer.hpp */
