#pragma once
#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED

#include <assert.h>
#include <algorithm> // std::copy, std::rotate
#include <cstddef> // size_t
#include <initializer_list>
#include <stdexcept>

namespace rabid
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
			m_first = new value_type[count];
			m_last = m_first + count;
		}

		template <typename InputIterator>
		vector(InputIterator first, InputIterator last)
		{
			difference_type count = std::distance(first, last);
			m_first = new value_type[count];
			m_last = m_first + count;

			std::copy(first, last, m_first);
		}

		vector(std::initializer_list<Type> init)
		{
			m_first = new value_type[init.size()];
			m_last = m_first + init.size();

			std::copy(init.begin(), init.end(), m_first);
		}

		vector(const vector& other)
		{
			m_first = new value_type[other.size()];
			m_last = m_first + other.size();

			std::copy(other.begin(), other.end(), m_first);
		}

		vector(vector&& other)
		{
			m_first = other.m_first;
			m_last = other.m_last;
			other.m_first = nullptr;
			other.m_last = nullptr;
		}

		~vector()
		{
			delete[] m_first;
		}

		//insert methods

		// returns iterator pointing to the inserted value
		iterator insert(const_iterator pos, const Type& value)
		{
			size_t ns = size() + 1;
			iterator n = new value_type[ns];

			size_t begin = 0;
			for (iterator r = m_first; r != pos; r++) {
				begin++;
			}

			n[begin] = value;
			std::copy(m_first, m_first + begin, n);
			std::copy(m_first + begin, m_last, n + begin + 1);

			delete[] m_first;
			m_first = n;
			m_last = n + ns;

			return m_first + begin;
		}

		// returns iterator pointing to a first inserted element
		template <typename InputIterator>
		iterator insert(const_iterator pos, InputIterator first, InputIterator last)
		{
			difference_type count = std::distance(first, last);
			size_t ns = size() + count;
			iterator n = new value_type[ns];

			size_t begin = 0;
			for (iterator r = m_first; r != pos; r++) {
				begin++;
			}

			std::copy(m_first, m_first + begin, n);
			std::copy(first, last, n + begin);
			std::copy(m_first + begin, m_last, n + begin + count);

			delete[] m_first;
			m_first = n;
			m_last = n + ns;

			return m_first + begin;
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
			if (pos >= size())
			{
				throw std::out_of_range("out of range");
			}

			return m_first[pos];
		}

		//your private functions

	private:
		iterator m_first;
		iterator m_last;
	};
}

#endif // VECTOR_H_INCLUDED
