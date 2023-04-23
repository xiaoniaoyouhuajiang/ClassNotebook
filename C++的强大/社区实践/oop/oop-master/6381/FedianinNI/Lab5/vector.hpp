#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <assert.h>
#include <algorithm> // std::copy, std::rotate
#include <cstddef> // size_t
#include <initializer_list>
#include <stdexcept>

namespace my_space{
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
			if (count){
				m_first = new Type [count];
				m_last = m_first + count;
			}
			else m_first = m_last = nullptr;
		}

		template <typename InputIterator>
		vector(InputIterator first, InputIterator last)
		{
			difference_type count = last - first;
			if (count){
				m_first = new Type [count];
				m_last = m_first + count;
				std::copy(first, last, m_first);
			}
			else m_first = m_last = nullptr;
		}

		vector(std::initializer_list<Type> init)
		{
			size_t count = init.size();
			if (count){
				m_first = new Type [count];
				m_last = m_first + count;
				std::copy(init.begin(), init.end(), m_first);
			}
			else m_first = m_last = nullptr;
		}

		vector(const vector& other)
		{
			size_t count = other.size();
			if (count){
				m_first = new Type [count];
				m_last = m_first + count;
				std::copy(other.begin(), other.end(), m_first);
			}
			else m_first = m_last = nullptr;
		}

		vector(vector&& other)
		{
			m_first = other.begin();
			m_last = other.end();
			other.m_first = other.m_last = nullptr;
		}

		~vector()
		{
			if (!empty()){
				delete [] m_first;
				m_first = m_last = nullptr;
			}
		}
		
		vector& operator=(const vector& other)
		{
			if (this != &other){
				if (!empty()){
					delete [] m_first;
					m_first = m_last = nullptr;
				}
				size_t count = other.size();
				if (count){
					m_first = new Type [count];
					m_last = m_first + count;
					std::copy(other.begin(), other.end(), m_first);
				}
			}
			return *this;
		}

		vector& operator=(vector&& other)
		{
			if (this != &other){
				if (!empty()){
					delete [] m_first;
					m_first = m_last = nullptr;
				}
				std::swap(m_first, other.m_first);
				std::swap(m_last, other.m_last);
			}
			return *this;
		}

		template <typename InputIterator>
		void assign(InputIterator first, InputIterator last)
		{
			if (!empty()){
				delete [] m_first;
				m_first = m_last = nullptr;
			}
			difference_type count = last - first;
			if (count){
				m_first = new Type [count];
				m_last = m_first + count;
				std::copy(first, last, m_first);
			}
			else m_first = m_last = nullptr;
		}
		
		void resize(size_t count)
		{
			if((count) && (count != size())){
				iterator temp = new Type[count];
				if(count > size())	std::copy(m_first, m_last, temp);
				else	std::copy(m_first, m_first + count, temp);
				if(!empty())	delete[] m_first;
				m_first = temp;
				m_last = m_first + count;
			}
			else if((!count) && (count != size())){
				delete[] m_first;
				m_last = m_first = nullptr;
			} 
		}

		iterator erase(const_iterator pos)
		{
			difference_type diff = pos - m_first;
			std::rotate(m_first + diff, m_first + diff + 1, m_last); //(pos, pos+1, m_last)
			resize(m_last - m_first - 1);
			return m_first + diff;
		}

		iterator erase(const_iterator first, const_iterator last)
		{
			difference_type diff = first - m_first;
			difference_type _size = last - first;
			std::rotate(m_first + diff, m_first + diff + _size, m_last); //(first, last, m_last)
			resize(m_last - m_first - _size);
			return m_first + diff;
		}
		
		iterator insert(const_iterator pos, const Type& value)
		{
			difference_type newpos = pos - m_first;
			iterator temp = new Type[size() + 1];
			std::copy(m_first, m_first + newpos, temp);
			temp[newpos] = value;
			std::copy(m_first + newpos, m_last, temp + newpos + 1);
			m_last = temp + size() + 1;
			if (m_first) delete [] m_first;
			m_first = temp;
			return m_first + newpos;
		}

		template <typename InputIterator>
		iterator insert(const_iterator pos, InputIterator first, InputIterator last)
		{
			difference_type newpos = pos - m_first;
			iterator temp = new Type[size() + (last - first)];
			std::copy(m_first, m_first + newpos, temp);
			std::copy(first, last, temp + newpos);
			std::copy(m_first + newpos, m_last, temp + newpos + (last - first));
			m_last = temp + size() + (last - first);
			if (m_first) delete [] m_first;
			m_first = temp;
			return m_first + newpos;
		}

		void push_back(const value_type& value)
		{
			iterator temp = new Type[size() + 1];
			std::copy(m_first, m_last, temp);
			temp[size()] = value;
			m_last = temp + size() + 1;
			if (m_first) delete [] m_first;
			m_first = temp;
		}
		
		reference at(size_t pos)
		{
			return checkIndexAndGet(pos);
		}

		const_reference at(size_t pos) const
		{
			return checkIndexAndGet(pos);
		}

		reference operator[](size_t pos)
		{
			return m_first[pos];
		}

		const_reference operator[](size_t pos) const
		{
			return m_first[pos];
		}

		iterator begin()
		{
			return m_first;
		}

		const_iterator begin() const
		{
			return m_first;
		}

		iterator end()
		{
			return m_last;
		}

		const_iterator end() const
		{
			return m_last;
		}

		size_t size() const
		{
			return m_last - m_first;
		}

		bool empty() const
		{
			return m_first == m_last;
		}

		private:   
		reference checkIndexAndGet(size_t pos) const
		{
			if (pos >= size())	throw std::out_of_range("out of range");
			return m_first[pos];
		}

		private:
		iterator m_first;
		iterator m_last;
	};
}

#endif
