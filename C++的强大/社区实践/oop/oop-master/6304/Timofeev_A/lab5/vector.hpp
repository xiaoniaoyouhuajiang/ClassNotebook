#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <assert.h>
#include <algorithm> // std::copy, std::rotate
#include <cstddef> // size_t
#include <initializer_list>
#include <stdexcept>
#include <iostream>
using namespace std;

namespace stepik
{
	template <typename Type> class vector
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
			if (count < 0) {
				throw invalid_argument("Argument can't be a negative number!");
			}
			else {
				m_first = new value_type[count];
				m_last = m_first + count;
			}
		}

		template <typename InputIterator>
		vector(InputIterator first, InputIterator last)
		{
			difference_type count = last - first;
			m_first = new Type[count];
			copy(first, last, this->m_first);
			m_last = m_first + count;
		}

		vector(std::initializer_list<Type> init)
		{
			m_first = new value_type[init.size()];
			copy(init.begin(), init.end(), this->m_first);
			m_last = m_first + init.size();
		}

		vector(const vector& other)
		{
			m_first = new value_type[other.size()];
			copy(other.m_first, other.m_last, this->m_first);
			m_last = m_first + other.size();
		}

		vector(vector&& other) : m_first(move(other.m_first)), m_last(move(other.m_last))
		{
			other.m_first = nullptr;
			other.m_last = nullptr;
		}

		~vector()
		{
			delete[] m_first;
		}

		//assignment operators
		vector& operator=(const vector& other)
		{
			delete[] m_first;
			m_first = new value_type[other.size()];
			copy(other.m_first, other.m_last, this->m_first);
			m_last = m_first + other.size();
			return *this;
		}

		vector& operator=(vector&& other)
		{
			delete[] m_first;
			m_first = other.m_first;
			m_last = other.m_last;
			other.m_first = nullptr;
			other.m_last = nullptr;
			return *this;
		}

		// assign method
		template <typename InputIterator>
		void assign(InputIterator first, InputIterator last)
		{
			delete[] m_first;
			difference_type count = last - first;
			m_first = new value_type[count];
			copy(first, last, m_first);
			m_last = m_first + count;
		}

		// resize methods
		void resize(size_t count)
		{
			if (size() != count) {
				if (count) {
					vector tmp(this);
					delete[] m_first;
					m_first = new value_type[count];
					m_last = m_first + count;
					if (tmp.size() < count) {
						copy(tmp.m_first, tmp.m_last, this->m_first);
					}
					else {
						copy(tmp.m_first, tmp.m_first + count, this->m_first);
					}
				}
				else {
					delete[] m_first;
					m_first = nullptr;
					m_last = nullptr;
				}
			}

		}

		//erase methods
		iterator erase(const_iterator pos)
		{
			iterator it = &m_first[pos - m_first];
			difference_type n = m_last - it - 1;
			memmove(it, it + 1, (n * sizeof(value_type)));
			m_last = m_last - 1;
			return it;
		}

		iterator erase(const_iterator first, const_iterator last)
		{
			iterator it = &m_first[m_last - first];
			iterator itt = &m_first[last - m_first];
			memmove(it, last, (m_last - itt) * sizeof(value_type));
			m_last = m_last - (last - first);
			return it;
		}
		//insert methods
		iterator insert(const_iterator pos, const Type& value)
		{
			size_t new_size = size() + 1;
			difference_type insert_pos = pos - begin();
			value_type *tmp = new value_type[new_size];
			iterator it_pos = &m_first[insert_pos];
			iterator it_ins = copy(m_first, it_pos, tmp);
			*(it_ins) = value;
			std::copy(it_pos, m_last, it_ins + 1);
			if (m_first) {
				delete[] m_first;
			}
			new (this) vector(new_size);
			std::copy(tmp, tmp + new_size, m_first);
			delete[] tmp;
			return m_first + insert_pos;
		}

		template <typename InputIterator>
		iterator insert(const_iterator pos, InputIterator first, InputIterator last)
		{
			difference_type insert_size = last - first;
			difference_type insert_pos = pos - begin();

			size_t new_size = size() + insert_size;
			value_type *tmp = new value_type[new_size];

			std::copy(m_first, m_first + insert_pos, tmp);
			std::copy(first, last, tmp + insert_pos);
			std::copy(m_first + insert_pos, m_last, tmp + insert_pos + new_size);
			if (m_first) {
				delete[] m_first;
			}
			new (this) vector(new_size);
			std::copy(tmp, tmp + new_size, m_first);
			delete[] tmp;
			return m_first + insert_pos;
		}

		//push_back methods
		void push_back(const value_type& value)
		{
			vector<Type> tmp;
			tmp = *this;
			delete[] m_first;
			m_first = new value_type[tmp.size() + 1];
			m_last = m_first + tmp.size() + 1;
			copy(tmp.begin(), tmp.end(), m_first);
			m_first[tmp.size()] = value;
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
#endif // !VECTOR_H

