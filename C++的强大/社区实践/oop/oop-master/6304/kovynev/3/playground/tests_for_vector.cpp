// OOP_3_1.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include <assert.h>
#include <algorithm> // std::copy, std::rotate
#include <cstddef> // size_t
#include <initializer_list>
#include <stdexcept>
#include <iostream>
using namespace std;
#pragma warning(disable:4996)


namespace stepik
{
	template <typename Type>
	class vector
	{
	public:
		typedef Type* iterator;
		typedef const Type* const_iterator;

		typedef Type value_type;

		typedef value_type& reference;
		typedef const value_type& const_reference;

		typedef std::ptrdiff_t difference_type;

		explicit vector(size_t count = 0)
		{
			m_first = new Type[count];
			m_last = &(m_first[count]);
			for (int i = 0; i < count; i++)
			{
				m_first[i] = 0;
			}

		}

		template <typename InputIterator>
		vector(InputIterator first, InputIterator last) :
			vector(last - first)
		{
			copy(first, last, m_first);
		}

		vector(std::initializer_list<Type> init) :
			vector(init.begin(), init.end()) {}

		vector(const vector& other)
		{
			m_first = new Type[other.size()];
			m_last = &(m_first[other.size()]);
			copy(other.m_first, other.m_last, m_first);
		}

		vector(vector&& other)
		{
			if (this != &other)
				swap(other);
		}

		~vector()
		{
			delete[] m_first;
		}

		vector& operator=(const vector& other)
		{
			if (this != &other)
				vector(other).swap(*this);
			return *this;
		}
		vector& operator=(vector&& other)
		{
			if (this != &other)
				swap(other);
			return *this;
		}
		
		template <typename InputIterator>
		void assign(InputIterator first, InputIterator last)
		{
			vector<Type>(first, last).swap(*this);
		}

		void resize(size_t count)
		{
			vector bufferVector(count);
			if (count > size())
			{
				std::move(m_first, m_last, bufferVector.m_first);
			}
			else
			{
				std::move(m_first,  m_first + count, bufferVector.m_first);
			}
			swap(bufferVector);
		}


		iterator erase(const_iterator pos)
		{
			size_t newPos = pos - m_first;
			std::rotate(const_cast<iterator>(pos), const_cast<iterator>(pos) + 1, m_last);
			resize(size() - 1);
			return m_first + newPos;
		}


		iterator erase(const_iterator first, const_iterator last)
		{
			size_t newPos = last - first;
			iterator newFirst = const_cast<iterator>(first);
			while (newPos != 0)
			{
				newFirst = erase(newFirst);
				newPos--;
			}
			return newFirst;
		}

		iterator insert(const_iterator pos, const Type& value)
		{
			size_t insertSize = pos - m_first;
			resize(size() + 1);
			iterator newPos = m_first + insertSize;
			std::rotate(newPos, m_last - 1, m_last);
			m_first[newPos - m_first] = value;
			return newPos;
		}

		template <typename InputIterator>
		iterator insert(const_iterator pos, InputIterator first, InputIterator last)
		{
			int d = last - first;
			iterator newPos = const_cast<iterator>(pos);
			while (d>0)
			{
				d--;
				newPos = insert(newPos, *(first + d));
			}
			return newPos;
		}

		//push_back methods
		void push_back(const value_type& value)
		{
			insert(m_last, value);
		}

		//at methods
		reference at(size_t pos)
		{
			return checkIndexAndGet(pos);
		}

		const_reference at(size_t pos) const
		{
			return checkIndexAndGet(pos);
		}

		//[] operators
		reference operator[](size_t pos)
		{
			return m_first[pos];
		}

		const_reference operator[](size_t pos) const
		{
			return m_first[pos];
		}

		//*begin methods
		iterator begin()
		{
			return m_first;
		}

		const_iterator begin() const
		{
			return m_first;
		}

		//*end methods
		iterator end()
		{
			return m_last;
		}

		const_iterator end() const
		{
			return m_last;
		}

		//size method
		size_t size() const
		{
			return m_last - m_first;
		}

		//empty method
		bool empty() const
		{
			return m_first == m_last;
		}

	private:
		reference checkIndexAndGet(size_t pos) const
		{
			if (pos > size())
			{
				//throw std::out_of_range("out of range");
			}

			return m_first[pos];
		}

		void swap(vector & other)
		{
			std::swap(this->m_first, other.m_first);
			std::swap(this->m_last, other.m_last);
		}

		iterator m_first;
		iterator m_last;
	};
}// namespace stepik
using namespace stepik;
int main()
{
	vector<int> a(10);
	cout << "\nCreate Vector - ";
	for (auto& t : a)
	{
		t = rand() % 10;
		cout << t << " ";
	}	

	//==========================================
	cout << "\nConstructor -";
	vector<int> b(a);
	for (const auto& t : b)
		cout << t << " ";;


	//==========================================
	vector<int> c(5);
	c = a;
	cout << "\nCopy -";
	for (const auto& t : c)
		cout << t << " ";

	//==========================================
	cout << "\nResize -";
	a.resize(6);
	for (const auto& t : a)
		cout << t << " ";

	//==========================================
	cout << "\nResize -";
	a.resize(12);
	for (const auto& t : a)
		cout << t << " ";

	//==========================================
	cout << "\nErase -";
	a.erase(a.end()-1);
	for (const auto& t : a)
		cout << t << " ";

	//==========================================
	cout << "\nErase -";
	a.erase(a.begin() + 1, a.end() - 2);
	for (const auto& t : a)
		cout << t << " ";

	//==========================================
	cout << "\nInsert -";
	a.insert(a.begin() + 1, 6);
	for (const auto& t : a)
		cout << t << " ";

	//==========================================
	cout << "\nInsert -";
	a.insert(a.begin() + 2, b.begin() + 1, b.end() - 1);
	for (const auto& t : a)
		cout << t << " ";

	//==========================================
	cout << "\nPush back -";
	a.push_back(13);
	for (const auto& t : a)
		cout << t << " ";

	return 0;
}