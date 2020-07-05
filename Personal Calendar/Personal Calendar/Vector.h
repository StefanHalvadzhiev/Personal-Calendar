#pragma once
#pragma once
#include <iostream>
using namespace std;
/// <summary>
/// This class has been used as a self-resizable date holder. You can push and erase elements at arbitrary positions 
/// </summary>
template<typename T>
class VectorArray {
private:
	/// <summary>
	/// Dynamic array which contains elements of type T
	/// </summary>
	T* t_array;

	/// Current amount of elements in t_array
	unsigned int currentElements;

	/// Maximum amount of elements in t_array
	unsigned int maxElements;

	/// Resizes t_array when maximum elements are reached
	void resizeArray();

	///Copy function used in operator= and copy constructor
	void copy(const VectorArray<T>& copyVector);
public:
	///Default constructor
	VectorArray();

	///Constructor with predefined size
	VectorArray(unsigned int size);

	///Destructor
	~VectorArray();

	///Copy constructor
	VectorArray(const VectorArray<T>& copyVector);

	///Operator =
	VectorArray& operator= (const VectorArray<T>& copyArray);

	/// Returns constant refference to an element in t_array
	const T& operator[](const unsigned int position) const;

	/// Returns refference to an element in t_array
	T& operator[](const unsigned int position);

	/// Empties t_array
	void clear();

	/// Creates t_array with give size
	void create(unsigned int size = 10);

	/// Checks whether t_array is empty
	bool isEmpty();

	/// Pushes an element in t_array
	void push(const T& new_t);

	/// Erases an element in a given position
	void erase(const unsigned int position);

	/// Returns the current size of t_array. If there are no elements or t_array is undefined - returns 0
	unsigned int getSize() const;
	void pushAt(unsigned int position, const T& new_t);
};


template<typename T>
void VectorArray<T>::pushAt(unsigned int position, const T& new_t) {
	if (position > currentElements-1)
		throw;
	if (currentElements == maxElements)
		resizeArray();
	currentElements++;
	for (unsigned int i = currentElements-1; i > position; i--) {
		t_array[i] = t_array[i - 1];
	}
	t_array[position] = new_t;
}

template<typename T>
void VectorArray<T>::erase(const unsigned int position) {
	for (unsigned int i = position; i < currentElements - 1; i++)
		t_array[i] = t_array[i+1];
	currentElements--;
}

template<typename T>
const T& VectorArray<T>::operator[](const unsigned int position) const {
	return t_array[position];
}

template<typename T>
T& VectorArray<T>::operator[](const unsigned int position) {
	return t_array[position];
}

template<typename T>
unsigned int VectorArray<T>::getSize() const {
	return currentElements;
}

template<typename T>
VectorArray<T>& VectorArray<T>::operator= (const VectorArray<T>& copyVector) {
	if (this != &copyVector) {
		clear();
		copy(copyVector);
	}
	return *this;
}

template<typename T>
VectorArray<T>::VectorArray(const VectorArray<T>& copyVector) {
	if (this != &copyVector) {
		copy(copyVector);
	}
}

template<typename T>
void VectorArray<T>::resizeArray() {
	T* buffer = new T[currentElements];

	for (unsigned int i = 0; i < currentElements; i++) // copying
		buffer[i] = t_array[i];

	unsigned int currentBuff = currentElements; // count of elements

	clear(); // clearing the array
	create(maxElements + 10); // creating new array

	for (unsigned int i = 0; i < currentBuff; i++)
		t_array[i] = buffer[i];
	currentElements = currentBuff;

	delete[] buffer;
}

template<typename T>
inline void VectorArray<T>::copy(const VectorArray<T>& copyVector) {
	create(copyVector.maxElements);
	currentElements = copyVector.currentElements;
	for (unsigned int i = 0; i < currentElements; i++)
		t_array[i] = copyVector.t_array[i];
}

template<typename T>
void VectorArray<T>::push(const T& new_t) {
	if (currentElements == maxElements)
		resizeArray();
	t_array[currentElements] = new_t;
	currentElements++;
}

template<typename T>
bool VectorArray<T>::isEmpty() {
	if (currentElements == 0)
		return true;
	return false;
}

template<typename T>
void VectorArray<T>::clear() {
	if (t_array != nullptr) {
		delete[] t_array;
		t_array = nullptr;
	}
}

template<typename T>
void VectorArray<T>::create(unsigned int size) {
	t_array = new T[size];
	currentElements = 0;
	maxElements = size;
}

template<typename T>
VectorArray<T>::VectorArray() {
	create();
}

template<typename T>
VectorArray<T>::~VectorArray() {
	clear();
}

template<typename T>
VectorArray<T>::VectorArray(unsigned int size) {
	create(size);
}