#include "GeneralBuffer.hpp"

template <class T>
GeneralBuffer<T>::GeneralBuffer() {
	arr = NULL;
	len = 0;
	allocated_length = 0;
}

template <class T>
GeneralBuffer<T>::GeneralBuffer(size_t length) {
	arr = new T[length]();
	len = 0;
	allocated_length = length;
}

template <class T>
void GeneralBuffer<T>::reset() {
	delete[] arr;
	arr = NULL;
	len = 0;
	allocated_length = 0;
}

template <class T>
void GeneralBuffer<T>::reset(size_t length) {
	delete[] arr;
	arr = new T[length]();
	len = 0;
	allocated_length = length;
}

template <class T>
void GeneralBuffer<T>::clear() {
	len = 0;
}

template <class T>
bool GeneralBuffer<T>::insertItemUniquely(T item) {
	if (arr == NULL) {
		arr = new T();
	}
	if (!checkItem(item)) {
		arr[len] = item;
		len++;
		return true;
	}
	return false;
}

template <class T>
void GeneralBuffer<T>::insertItem(T item) {
	if (arr == NULL) {
		arr = new T();
	}
	arr[len] = item;
	len++;
}

template <class T>
T& GeneralBuffer<T>::operator[](unsigned int index) {
	return arr[index];
}

template <class T>
void GeneralBuffer<T>::reduceUniquely(T item) {
	for (size_t i = 0; i < len; i++) {
		if (arr[i] == item) {
			reduceShiftList(i);
			break;
		}
	}
}

template <class T>
void GeneralBuffer<T>::reduceShiftList(unsigned int start_index) {
	T temp = arr[start_index];
	for (size_t i = start_index; i < len - 1; i++) arr[i] = arr[i + 1];
	arr[len - 1] = temp;
	len--;
}

template <class T>
bool GeneralBuffer<T>::checkItem(T item) {
	for (size_t i = 0; i < len; i++) if (arr[i] == item) return true;
	return false;
}

template <class T>
T* GeneralBuffer<T>::getArray() {
	return arr;
}

template <class T>
size_t GeneralBuffer<T>::length() {
	return len;
}

template <class T>
size_t GeneralBuffer<T>::memory_length() {
	return allocated_length;
}