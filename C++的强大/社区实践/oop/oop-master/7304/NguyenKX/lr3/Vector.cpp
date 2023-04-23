// LR3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
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

		explicit vector(size_t count = 0) : m_first(count?new Type[count]:nullptr), m_last(count?m_first+count:nullptr){}

		template <typename InputIterator>
		vector(InputIterator first, InputIterator last) 
			: m_first((last - first) ? new Type[last - first] : nullptr)
			, m_last((last - first) ? m_first + (last - first) : nullptr)
		{
			if (last - first > 0) {
				std::copy(first, last, this->m_first);
			}
		}

		vector(std::initializer_list<Type> init) 
			: m_first(init.size() ? new Type[init.size()] : nullptr)
			, m_last(init.size() ? m_first + init.size() : nullptr)
		{
			if (init.size() > 0) {
				std::copy(init.begin(), init.end(), this->m_first);
			}
		}

		// copy constructor
		vector(const vector& other)
		{
			// implement this
			size_t count = other.size();
			if (count != 0) {
				this->m_first = new Type[count];
				this->m_last = this->m_first + count;
				std::copy(other.begin(), other.end(), this->m_first);
			}
			else {
				m_first = nullptr;
				m_last = nullptr;
			}
		}

		// move constructor
		vector(vector&& other)
		{
			// implement this
			this->m_first = other.begin();
			this->m_last = other.end();
			other.m_first = nullptr;
			other.m_last = nullptr;
		}

		~vector()
		{
			// implement this
			if (m_first != nullptr) {
				delete[] m_first;
				m_first = nullptr;
				m_last = nullptr;
			}
		}

		//assignment operators
		vector& operator=(const vector& other)
		{
			// implement this
			if (m_first != nullptr) { delete[] m_first; }
			size_t size = other.size();
			if (size > 0) {
				this->m_first = new Type[size];
				this->m_last = this->m_first + size;
				std::copy(other.begin(), other.end(), this->m_first);
			}
			else {
				this->m_first = nullptr;
				this->m_last = nullptr;
			}
		}

		vector& operator=(vector&& other)
		{
			// implement this
			if (m_first != nullptr) { delete[] m_first; }
			this->m_first = other.begin();
			this->m_last = other.end();
			other.m_first = nullptr;
			other.m_last = nullptr;
		}

		// assign method
		template <typename InputIterator>
		void assign(InputIterator first, InputIterator last)
		{
			// implement this
			if (m_first != nullptr) { delete[] m_first; }
			if (first >= last) {
				m_first = nullptr; m_last = nullptr;
				return;
			}
			size_t count = last - first;
			this->m_first = new Type[count];
			this->m_last = this->m_first + count;
			std::copy(first, last, this->m_first);
		}

		// resize methods
		void resize(size_t count)
		{
			// implement this
			if (count == this->size()) return;
			if (count == 0) {
				delete[] this->m_first;
				this->m_first = nullptr;
				this->m_last = nullptr;
				return;
			}
			iterator temp = new Type[count];
			iterator des = temp;
			for (iterator src = this->begin(); src < this->end() && des - temp < count; src++)
			{
				*des = *src;
				des++;
			}
			delete[] this->m_first;
			this->m_first = temp;
			this->m_last = this->m_first + count;
		}

		//erase methods
		iterator erase(const_iterator pos)
		{
			// implement this
			if (pos < m_first || pos >= m_last) return this->m_last;
			size_t new_size = this->size() - 1;
			iterator temp = new Type[new_size];
			iterator des = temp;
			iterator ret = temp;
			for (iterator src = this->begin(); src < this->end(); src++)
				if (src != pos) {
					*des = *src;
					des++;
				}
				else {
					ret = des;
				}
			delete[] this->m_first;
			this->m_first = temp;
			this->m_last = this->m_first + new_size;
			return ret;
		}

		iterator erase(const_iterator first, const_iterator last)
		{
			// implement this
			size_t new_size = this->size() - (last - first);
			iterator temp = new Type[new_size];
			iterator des = temp;
			iterator ret = temp;
			for (iterator src = this->begin(); src < this->end(); src++)
				if (src < first || src >= last) {
					*des = *src;
					des++;
				}
				else {
					ret = des;
				}
			delete[] this->m_first;
			this->m_first = temp;
			this->m_last = this->m_first + new_size;
			return ret;
		}

		//insert methods
		iterator insert(const_iterator pos, const Type& value)
		{
			// implement this
			size_t new_size = this->size() + 1;
			iterator temp = new Type[new_size];
			iterator des = temp;
			iterator ret = nullptr;
			for (iterator src = this->begin(); src < this->end(); src++)
				if (src != pos) {
					*des = *src;
					des++;
				}
				else {
					*des = value;
					if (ret == nullptr) ret = des;
					des++;
					*des = *src;
					des++;
				}
			if (ret == nullptr) {
				*des = value;
				ret = des;
			}

			delete[] this->m_first;
			this->m_first = temp;
			this->m_last = this->m_first + new_size;
			return ret;
		}
		template <typename InputIterator>
		iterator insert(const_iterator pos, InputIterator first, InputIterator last)
		{
			iterator new_pos = const_cast<iterator>(pos);			
			for(InputIterator iter = last-1;iter>=first;iter--){
				new_pos = insert(new_pos, *(iter));
			}
			return new_pos;
		}

		//push_back methods
		void push_back(const value_type& value)
		{
			insert(this->end, value);
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

#include <iostream>
#include <vector>
int main2()
{
	stepik::vector<int> a(5);
	a[0] = 7;
	a[1] = 8;
	a[2] = 9;

	stepik::vector<int> b(3);
	for (int i = 0; i < b.size(); i++) {
		b[i] = i;
	}
	std::cout << b.insert(b.begin()-1, a.begin(), a.begin() + 3) << "  \n" << b.begin() << "  \n" << b.end() << std::endl;
	for (int i = 0; i < b.size(); i++) {
		std::cout << b.at(i) << " ";
	}
	return 0;
}

