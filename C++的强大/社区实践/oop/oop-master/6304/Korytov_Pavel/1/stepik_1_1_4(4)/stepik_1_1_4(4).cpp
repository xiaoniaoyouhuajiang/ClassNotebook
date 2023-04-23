#include "stdafx.h"
#include <iostream>
#include <assert.h>
#include <algorithm> // std::copy
#include <cstddef> // size_t
#include <iterator>
#include <memory>

using namespace std;
using namespace stdext;

template<typename T>
class Array
{
public:
	// (default) constructor
	Array(const size_t size = 0)
		: m_size(size)
		, m_array(m_size ? new T[m_size]() : nullptr)
	{
		cout << "I am born (by default)!" << endl;
	}

	void out() {
		for (int i = 0; i < (int)m_size; i++) {
			cout << i << ": " << m_array[i] << endl;
		}
	}

	void fill(const T x) {
		for (int i = 0; i < size(); i++) {
			m_array[i] = x;
		}
	}
	friend void swap(Array& first, Array& second)
	{
		cout << "Swapping stuff" << endl;
		swap(first.m_size, second.m_size);
		swap(first.m_array, second.m_array);
	}

	Array(const Array& arr)
		: m_size(arr.m_size),
		m_array(m_size ? new T[m_size] : nullptr)
	{
		cout << "Consructing stuff by copy" << endl;
		copy(arr.m_array.get(), arr.m_array.get() + m_size, checked_array_iterator<T*>(m_array.get(), m_size));
	}

	Array& operator=(Array arr) {
		cout << "Assigning stuff" << endl;
		swap(*this, arr);
		return *this;
	}

	
	Array(Array&& arr) {
		cout << "Moving stuff" << endl;
		swap(*this, arr);
	} 
	Array& operator=(Array&& arr) {
		cout << "Assingning and moving stuff" << endl;
		swap(*this, arr);
		return *this;
	}

	const size_t size() const
	{
		return m_size;
	}

	T& operator [](const size_t index)
	{
		assert(index < m_size);
		return m_array[index];
	}


private:
	size_t m_size;
	unique_ptr<T[]> m_array;
};

int main()
{
	cout << "----------------" << endl;
	//Checking constuctor
	Array<int> a1(3);
	a1.fill(666);
	cout << "Out a1" << endl;
	a1.out();
	cout << "----------------" << endl;
	//Checking copying
	Array<int> a2(a1);
	cout << "Out a1" << endl;
	a1.out();
	cout << "Out a2" << endl;
	a2.out();
	cout << "----------------" << endl;
	//Checking assigning
	Array<int> a3;
	a3 = a1;
	cout << "Out a1" << endl;
	a1.out();
	cout << "Out a3" << endl;
	a3.out();
	cout << "----------------" << endl;
	//Checking moving
	Array<int>a4 = std::move(a1);
	Array<int>a5(std::move(a2));
	cout << "Out a1" << endl;
	a1.out();
	cout << "Out a4" << endl;
	a4.out();
	cout << "Out a5" << endl;
	a5.out();
	return 0;
}

