#ifndef MVECTOR_H
#define MVECTOR_H

#include <assert.h>
#include <algorithm> // std::copy, std::rotate
#include <cstddef> // size_t
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

		//default constructor
		explicit vector(size_t count = 0)
		{
			if (count)
			{
				m_first = new Type[count];
				m_last = m_first + count;
			}
			else
				m_first = m_last = nullptr;
		}

		template <typename InputIterator>
		vector(InputIterator first, InputIterator last)
			:vector(last - first)
		{
			if(!empty())
				std::copy(first,last,m_first);
		}

		//constructor with init list
		vector(std::initializer_list<Type> init)
			:vector(init.begin(), init.end())
		{}

		//copy constructor
		vector(const vector& other)
			:vector(other.begin(), other.end())
		{}

		//move constructor
		vector(vector&& other)
			:vector()  //init iterators with nullptr
		{
			std::swap(m_first, other.m_first);
			std::swap(m_last, other.m_last);
		}

		//copy assignment
		vector & operator =(const vector & other)
		{
			if(this != &other)
				this->assign(other.begin(),other.end());
			return *this;
		}

		//move assignment
		vector & operator=(vector&& other)
		{
			std::swap(m_first, other.m_first);
			std::swap(m_last, other.m_last);
			return *this;
		}

		template <typename InputIterator>
		void assign(InputIterator first, InputIterator last)
		{
			this->~vector();
			if(first==last)
				m_first = m_last = nullptr;
			else
			{
				difference_type count=last-first;
				m_first = new Type[count];
				m_last = m_first + count;
				std::copy(first,last,m_first);
			}
		}

		~vector()
		{
				delete[] m_first;
		}


		void resize(size_t count)
		{
			if(count == size())
				return;

			if(count==0)
			{
				this->assign(m_first,m_first);
				return;
			}

			iterator t = new Type[count];

			if(count>size())
				std::copy(m_first,m_last,t);
			else
				std::copy(m_first,m_first+count,t);
			this->assign(t ,t+count);
			delete [] t;
		}

		iterator erase(const_iterator pos)
		{
			if(pos< m_first || pos>= m_last)
				throw std::out_of_range("not in the range (erase)");

			difference_type erasing_el = pos-m_first;
			std::rotate(m_first+erasing_el,m_first+erasing_el+1,m_last);
			resize(size()-1);
			return m_first + erasing_el;
		}

		iterator erase(const_iterator first,const_iterator last)
		{
			if (first < m_first || first > m_last || last < m_first || last > m_last  || last<first)
			  throw std::out_of_range("not in the range (erase)");

			difference_type erasing_el=first-m_first;
			difference_type num_of_erase=last-first;
			std::rotate(m_first+erasing_el,m_first+erasing_el+num_of_erase,m_last);
			resize(size()-num_of_erase);
			return m_first + erasing_el;
		}

		void push_back(const value_type& value)
		{
			resize(size()+1);
			m_first[size()-1] = value;
		}

		iterator insert(const_iterator pos, const Type& value)
		{
			if (pos < m_first || pos > m_last)
				throw std::out_of_range("not in the range (insert)");

			difference_type ins_el = pos-m_first;
			push_back(value);

			std::rotate(m_first+ins_el,m_last-1,m_last);

			return m_first + ins_el;
		}

		template<typename InputIterator>
		iterator insert(const_iterator pos, InputIterator first, InputIterator last)
		{
			if (pos < m_first || pos > m_last)
				throw std::out_of_range("not in the range (insert)");

			difference_type n_pos = pos - m_first;
			difference_type num_of_el = last - first;
			resize(size()+num_of_el);

			std::rotate(m_first+n_pos,m_last-num_of_el,m_last);
			std::copy(first,last,m_first + n_pos);

			return m_first + n_pos;
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
			for (unsigned int i = 0; i < size(); i++)
				std::cout << m_first[i] << ' ';
			std::cout << "\nsize is " << size() << '\n' <<std::endl;
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

		iterator m_first;
		iterator m_last;
	};
}// namespace stepik

#endif
