#pragma once

#include "memory/memory.h"

struct out_of_range
{

};

template<class T> class Vector
{
public:
	/* ----- Constructors ----- */

	// Default constructor
	Vector();

	explicit Vector(size_t s);

	// Copy constructor
	Vector(const Vector& arg);

	// Copy Assingment
	Vector<T>& operator=(const Vector<T>& arg);

	// Destructor
	~Vector();

	/*----------------------------*/





	/* -------- ITERATORS --------*/

	class iterator;

	iterator Begin();

	const iterator Begin() const;

	iterator End();
	
	const iterator End() const;

	const iterator ConstBegin() const;

	const iterator ConstEnd() const;

	/*----------------------------*/





	/* -------- CAPACITY -------- */

	bool Empty() const;

	// Returns size of allocated storate capacity
	size_t Capacity() const;

	// Requests a change in capacity
	// reserve() will never decrase the capacity.
	void Reserve(size_t new_size);

	// Changes the Vector's size.
	// If the newsize is smaller, the last elements will be lost.
	// Has a default value param for custom values when resizing.
	void Resize(size_t new_size, T val = T());

	// Returns the size of the Vector (number of elements). 
	size_t Size() const;

	// Returns the maximum number of elements the Vector can hold
	size_t MaxSize() const;

	// Reduces capcity to fit the size
	void ShrinkToFit();

	/*----------------------------*/





	/* -------- MODIFIERS --------*/

	// Removes all elements from the Vector
	// Capacity is not changed.
	void Clear();

	// Inserts element at the back
	void PushBack(const T& d);

	// Removes the last element from the Vector
	void PopBack();

	// Append a vector.
	void Append(const Vector<T>& v);

	/*----------------------------*/





	/* ----- ELEMENT ACCESS ----- */

	// Access elements with bounds checking
	T& At(size_t n);

	// Access elements with bounds checking for constant Vectors.
	const T& At(size_t n) const;

	// Access elements, no bounds checking
	T& operator[](size_t i);

	// Access elements, no bounds checking
	const T& operator[](size_t i) const;

	// Returns a reference to the first element
	T& Front();

	// Returns a reference to the first element
	const T& Front() const;

	// Returns a reference to the last element
	T& Back();

	// Returns a reference to the last element
	const T& Back() const;

	// Returns a posize_ter to the array used by Vector
	T* Data();

	// Returns a posize_ter to the array used by Vector
	const T* Data() const;

	/*----------------------------*/

private:
	size_t	size_;		// Number of elements in Vector
	T*		elements_;	// Posize_ter to first element of Vector
	size_t	space_;		// Total space used by Vector including
						// elements and free space.
};



template<class T> class Vector<T>::iterator
{
public:
	iterator(T* p)
		:curr_(p)
	{}

	iterator& operator++()
	{
		curr_++;
		return *this;
	}

	iterator& operator--()
	{
		curr_--;
		return *this;
	}

	T& operator*()
	{
		return *curr_;
	}

	bool operator==(const iterator& b) const
	{
		return *curr_ == *b.curr_;
	}

	bool operator!=(const iterator& b) const
	{
		return *curr_ != *b.curr_;
	}

private:
	T* curr_;
};



// Constructors/Destructor
template<class T>
inline Vector<T>::Vector()
	:size_(0), elements_(0), space_(0)
{}


template<class T>
inline Vector<T>::Vector(size_t s)
	:size_(s), elements_(new T[s]), space_(s)
{
	for (size_t index = 0; index < size_; ++index)
		elements_[index] = T();
}


template<class T>
inline Vector<T>::Vector(const Vector & arg)
	:size_(arg.size_), elements_(new T[arg.size_])
{
	for (size_t index = 0; index < arg.size_; ++index)
		elements_[index] = arg.elements_[index];
}

template<class T>
inline Vector<T>& Vector<T>::operator=(const Vector<T>& a)
{
	if (this == &a) return *this;	// Self-assingment not work needed

									// Current Vector has enough space, so there is no need for new allocation
	if (a.size_ <= space_)
	{
		for (size_t index = 0; index < a.size_; ++index)
		{
			elements_[index] = a.elements_[index];
			size_ = a.size_;
			return *this;
		}
	}

	T* p = new T[a.size_];

	for (size_t index = 0; index < a.size_; ++index)
		p[index] = a.elements_[index];

	delete[] elements_;
	size_ = a.size_;
	space_ = a.size_;
	elements_ = p;
	return *this;
}

template<class T>
Vector<T>::~Vector()
{
	delete[] elements_;
}



// Iterators
template<class T>
inline typename Vector<T>::iterator Vector<T>::Begin()
{	
	return Vector<T>::iterator(&elements_[0]);
}

template<class T>
inline const Vector<T>::iterator Vector<T>::Begin() const
{
	return Vector<T>::iterator(&elements_[0]);
}

template<class T>
inline Vector<T>::iterator Vector<T>::End()
{
	return Vector<T>::iterator(&elements_[size_]);
}

template<class T>
inline const Vector<T>::iterator Vector<T>::End() const
{
	return Vector<T>::iterator(&elements_[size_]);
}

template<class T>
inline const Vector<T>::iterator Vector<T>::ConstBegin() const
{
	return Vector<T>::iterator(&elements_[0]);
}

template<class T>
inline const Vector<T>::iterator Vector<T>::ConstEnd() const
{
	return Vector<T>::iterator(&elements_[size_]);
}



// Capacity
template<class T>
inline bool Vector<T>::Empty() const
{
	return (size_ == 0);
}

template<class T>
inline size_t Vector<T>::Capacity() const
{
	return space_;
}

template<class T>
inline void Vector<T>::Reserve(size_t new_size)
{
	if (new_size <= space_) return;

	T* p = new T[new_size];

	for (size_t i = 0; i < size_; ++i)
		p[i] = elements_[i];

	delete[] elements_;

	elements_ = p;

	space_ = new_size;
}

template<class T>
inline void Vector<T>::Resize(size_t new_size, T val)
{
	Reserve(new_size);

	for (size_t index = size_; index < new_size; ++index)
		elements_[index] = T();

	size_ = new_size;
}

template<class T>
inline size_t Vector<T>::Size() const
{
	return size_;
}



template<class T>
inline void Vector<T>::Clear()
{
	for (size_t index = 0; index < size_; ++index)
		elements_[index] = T();
	space_ += size_ * sizeof(T);
	size_ = 0;
}

// Modifiers
template<class T>
inline void Vector<T>::PushBack(const T& d)
{
	if (space_ == 0)
		Reserve(8);
	else if (size_ == space_)
		Reserve(2 * space_);

	elements_[size_] = d;

	++size_;
}

template<class T>
inline void Vector<T>::Append(const Vector<T>& v)
{
	Reserve(max(v.Size(), size_)*2);

	for (size_t index = 0; index < v.Size(); ++index)
		elements_[index + size_] = v[index];

	size_ += v.Size();

}



// Accessors
template<class T>
inline T & Vector<T>::At(size_t n)
{
	if (n < 0 || size_ <= n) throw out_of_range();
	return elements_[n];
}

template<class T>
inline const T & Vector<T>::At(size_t n) const
{
	if (n < 0 || size_ <= n) throw out_of_range();
	return elements_[n];
}

template<class T>
inline T & Vector<T>::operator[](size_t i)
{
	return elements_[i];
}

template<class T>
inline const T & Vector<T>::operator[](size_t i) const
{
	return elements_[i];
}

template<class T>
inline T& Vector<T>::Front()
{
	return elements_[0];
}

template<class T>
inline const T& Vector<T>::Front() const
{
	return elements_[0];
}

template<class T>
inline T& Vector<T>::Back()
{
	return elements_[size_ - 1];
}

template<class T>
inline const T& Vector<T>::Back() const
{
	return elements_[size_ - 1];
}

template<class T>
inline T* Vector<T>::Data()
{
	return elements_;
}

template<class T>
inline const T* Vector<T>::Data() const
{
	return elements_;
}

