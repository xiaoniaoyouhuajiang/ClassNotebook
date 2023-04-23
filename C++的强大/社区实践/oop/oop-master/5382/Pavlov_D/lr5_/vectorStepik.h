#pragma once
#pragma once
#include <assert.h>
#include <algorithm> 
#include <cstddef> 
#include <initializer_list>
#include <stdexcept>
#include <iostream>

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
			if (count != 0)
				memoryAllocation(count);
			else
			{
				m_first = nullptr;
				m_last = nullptr;
			}
		}

		template <typename InputIterator>
		vector(InputIterator first, InputIterator last)
			: vector(last - first)
		{
			std::copy(first, last, m_first);
		}

		vector(std::initializer_list<Type> init)
			: vector(init.begin(), init.end())
		{
		}

		vector(const vector& other)
		{
			memoryAllocation(other.size());
			try
			{
				std::copy(other.m_first, other.m_last, m_first);
			}
			catch (...)
			{
				delete[] m_first;
				throw;
			}
		}

		vector(vector&& other)
			:m_first(other.m_first), m_last(other.m_last)
		{
			other.m_first = nullptr;
			other.m_last = nullptr;
		}


		vector& operator=(const vector& other)
		{
			delete[] m_first;
			memoryAllocation(other.size());
			std::copy(other.m_first, other.m_last, m_first);
		}

		vector& operator=(vector&& other)
		{
			if (this != &other)
				delete[] m_first;
			m_first = other.m_first;
			m_last = other.m_last;
			other.m_first = nullptr;
			other.m_last = nullptr;
			return *this;
		}

		template <typename InputIterator>
		void assign(InputIterator first, InputIterator last)
		{
			delete[] m_first;
			memoryAllocation(last - first);
			std::copy(first, last, m_first);
		}

		~vector()
		{
			delete[] m_first;
		}

		void memoryAllocation(size_t count)
		{
			m_first = new Type[count];
			m_last = m_first + count;
		}

		void memoryAllocation(size_t count, Type* temp)
		{
			delete[] m_first;
			m_first = temp;
			m_last = m_first + count;
		}

		void resize(size_t count)
		{
			vector new_vec(count);
			std::copy(begin(), begin() + count > end() ? end() : begin() + count, new_vec.begin());
			new_vec.swap(*this);
		}

		iterator erase(const_iterator pos)
		{
			return erase(pos, pos + 1);
		}

		iterator erase(const_iterator first, const_iterator last)
		{
			vector new_vec(size() - (last - first));
			size_t n = (first - begin());
			std::copy(const_iterator(begin()), first, new_vec.begin());
			std::copy(last, const_iterator(end()), new_vec.begin() + n);
			new_vec.swap(*this);
			return begin() + n;
		}

		void swap(vector &obj) throw()
		{
			std::swap(m_first, obj.m_first);
			std::swap(m_last, obj.m_last);
		}

		void push_back(const value_type& value)
		{
			insert(m_last, value);
		}

		iterator insert(const_iterator pos, const Type& value)
		{
			iterator a = (iterator)&value;
			return insert(pos, a, a + 1);
		}

		template <typename InputIterator>
		iterator insert(const_iterator pos, InputIterator first, InputIterator last)
		{
			int count = size() + (last - first);
			int res = pos - m_first;
			Type *temp = new Type[count];
			std::copy(m_first, (iterator)pos, temp);
			int j = 0;
			for (int i = res; i < res + (last - first); i++)
			{
				temp[i] = first[j];
				j++;
			}
			for (int i = res + (last - first); i < count; i++)
				temp[i] = m_first[i - (last - first)];
			memoryAllocation(count, temp);
			return m_first + res;
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

		void print()
		{
			for (int i = 0; i < size(); i++)
				std::cout << m_first[i] << std::endl;
			std::cout << "\n";
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
