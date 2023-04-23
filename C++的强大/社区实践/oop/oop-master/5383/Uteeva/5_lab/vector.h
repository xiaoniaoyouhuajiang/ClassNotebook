#ifndef lab5_vector_H
#define lab5_vector_H
#include <assert.h>
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
			for (int i = 0; count > i; i++)
			{
				m_first[i] = 0;
			}
			m_last = m_first + count;
		}

		template <typename InputIterator>
		vector(InputIterator first, InputIterator last)
		{
			size_t sz;
			sz = last - first;
			m_first = new Type[sz];
			m_last = m_first + sz;

			std::copy(first, last, m_first);

		}

		vector(std::initializer_list <Type> init) : vector(init.begin(), init.end())
		{

		}

		vector(const vector& other) : vector(other.begin(), other.end())
		{

		}

		vector(vector&& other)
		{
			m_first = other.m_first;
			m_last = other.m_last;
			other.m_first = nullptr;
			other.m_last = nullptr;
		}

		vector& operator = (const vector& other)
		{
			vector vctr(other);
			swap(vctr);
			return *this;
		}

		vector& operator = (vector&& other)
		{
			if (this != &other) {
				delete[] m_first;
				m_first = other.m_first;
				m_last = other.m_last;
				other.m_first = nullptr;
				other.m_last = nullptr;
			}

		}

		~vector()
		{
			delete[] m_first;
		}

		// resize methods
		void resize(size_t count)
		{
			size_t sz;
			iterator last;
			sz = m_last - m_first;
			if (count >= sz) last = m_last;
			else last = m_first + count;
			vector vctr(count);
			std::move(m_first, last, vctr.m_first);
			std::swap(this->m_first, vctr.m_first);
			std::swap(this->m_last, vctr.m_last);
		}


		//insert methods
		iterator insert(const_iterator pos, const Type& value)
		{
			size_t n = pos - m_first;
			push_back(value);
			std::rotate(m_first + n, m_last - 1, m_last);
			return m_first + n;
		}

		template <typename InputIterator>
		iterator insert(const_iterator pos, InputIterator first, InputIterator last)
		{
			size_t sz;
			sz = last - first;
			iterator tmp = const_cast<iterator>(pos);
			while (sz)
			{
				tmp = insert(tmp, first[sz - 1]);
				--sz;
			}
			return tmp;
		}

		//push_back methods
		void push_back(const value_type& value)
		{
			resize(size() + 1);
			m_first[size() - 1] = value;
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
}// namespace stepik

#endif // VECTORSTEPIK_H
