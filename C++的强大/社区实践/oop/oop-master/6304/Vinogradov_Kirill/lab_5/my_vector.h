#pragma once
#include <assert.h>
#include <cstring>
#include <algorithm> // std::copy, std::rotate
#include <cstddef> // size_t
#include <initializer_list>
#include <stdexcept>

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
			m_last = m_first + count;
		}

		template <typename InputIterator>
		vector(InputIterator first, InputIterator last)
		{
			ptrdiff_t count = last - first;
			m_first = new Type[count];
			for (ptrdiff_t i = 0; i < count; i++, first++)
			{
				m_first[i] = *first;
			}
			m_last = m_first + count;
		}

		vector(std::initializer_list<Type> init)
		{
			m_first = new Type[init.size()];
			size_t i = 0;
			for (auto elem : init)
			{
				m_first[i++] = elem;
			}
			m_last = m_first + init.size();
		}

		vector(const vector& other)
		{
			size_t count = other.size();
			m_first = new Type[count];
			for (size_t i = 0; i < count; i++)
			{
				m_first[i] = other[i];
			}
			m_last = m_first + count;
		}

		void swap(vector& first, vector& second)
		{
			using std::swap;
			swap(first.m_first, second.m_first);
			swap(first.m_last, second.m_last);
		}

		vector(vector&& other)
		{
			swap(*this, other);
		}

		~vector()
		{
			delete[] m_first;
		}

		//assignment operators
		vector& operator=(const vector& other)
		{
			size_t count = other.size();
			delete [] m_first;
			m_first = new Type[count];
			for (size_t i = 0; i < count; i++)
			{
				m_first[i] = other.m_first[i];
			}
			m_last = m_first + count;
			return *this;
		}

		vector& operator=(vector&& other)
		{
			swap(*this, other);
		}

		// assign method
		template <typename InputIterator>
		void assign(InputIterator first, InputIterator last)
		{
			size_t count = last - first;
			delete[] m_first;
			m_first = new Type[count];
			for (size_t i = 0; i < count; i++, first++)
			{
				m_first[i] = *first;
			}
			m_last = m_first + count;
		}

		// resize methods
		void resize(size_t count)
		{
			vector temp = *this;
			delete[] m_first;
			m_first = new Type[count];
			m_last = m_first + count;
			count = count > temp.size() ? temp.size() : count;			
			for (size_t i = 0; i < count; i++)
			{
				m_first[i] = temp.m_first[i];
			}			
		}

		//erase methods
		iterator erase(const_iterator pos)
		{
			iterator temp = &m_first[pos - m_first];
			if (pos >= m_last)
			{
				return temp;
			}			
			size_t count = m_last - temp - 1;
			memmove(temp, temp+1, count* sizeof(Type));
			m_last--;
			return temp;
		}

		iterator erase(const_iterator first, const_iterator last)
		{
			iterator temp_f = &m_first[first - m_first];
			if (first == last || first >= m_last || last > m_last)
			{
				return temp_f;
			}
			if (first - last == 1)
			{
				temp_f = erase(first);
				return temp_f;
			}			
			iterator temp_l = &m_first[last - m_first];
			size_t count = m_last - temp_l;
			memmove(temp_f, temp_l, count * sizeof(Type));
			m_last -= last - first;
			return temp_f;
		}

		//insert methods
		iterator insert(const_iterator pos, const Type& value)
		{
			size_t count = size() + 1;
			Type* temp = new Type[count];
			iterator iter = &m_first[pos - m_first];
			iterator value_pos = std::copy(m_first, iter, temp);
			*(value_pos) = value;
			std::copy(iter, m_last, value_pos + 1);
			delete[] m_first;
			m_first = new Type[count];
			std::copy(temp, temp + count, m_first);
			delete[] temp;
			m_last = m_first + count;
			return &m_first[pos - m_first];
		}

		template <typename InputIterator>
		iterator insert(const_iterator pos, InputIterator first, InputIterator last)
		{
			size_t count = (pos - begin());
			if (pos > m_last || first == last)
			{
				return begin() + count;
			}
			vector temp (size() + (last - first));			
			std::copy(const_iterator(begin()), pos, temp.begin());
			std::copy(first, last, temp.begin() + count);
			if (pos + 1 < end())
				std::copy(pos, const_iterator(end()), temp.begin() + count + (last - first));
			temp.swap(temp, *this);
			return begin() + count;
		}

		//push_back methods
		void push_back(const value_type& value)
		{
			vector temp = *this;
			size_t count = size() + 1;
			delete[] m_first;
			m_first = new Type[count];
			m_last = m_first + count;
			for (auto & el : temp)
			std::copy(temp.begin(), temp.end(), m_first);
			m_first[count - 1] = value;
		}

		//print method
		void print()
		{
			for (size_t i = 0; i < this->size(); i++)
			{
				std::cout << this->at(i) << std::endl;
			}
			std::cout << "vector size " << this->size() << std::endl;
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

	public:
		iterator m_first;
		iterator m_last;
	};
}// namespace stepik