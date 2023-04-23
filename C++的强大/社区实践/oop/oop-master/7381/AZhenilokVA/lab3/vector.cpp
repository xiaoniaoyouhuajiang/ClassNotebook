//#include "pch.h"
#include <iostream>
#include <assert.h>
#include <algorithm> // std::copy, std::rotate
#include <cstddef> // size_t
#include <initializer_list>
#include <stdexcept>
using namespace std;


//функция компаратор для int
int comp(const void* x1, const void* x2) {
	return *(const int*)x1 - *(const int*)x2;
}

namespace stepic{
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
			if (count == 0) {
				m_first = nullptr;
				m_last = nullptr;
			}
			else {
				m_first = new Type[count];
				m_last = m_first + count;
			}
		}

		template <typename InputIterator>
		vector(InputIterator first, InputIterator last)
			: vector(last - first)
		{
			std::copy(first, last, m_first);
		}

		vector(std::initializer_list<Type> init)
			: vector(init.size())
		{
			size_t i = 0;
			for (auto& element : init) {
				m_first[i] = element;
				i++;
			}
		}

		vector(const vector& other)
			: vector(other.begin(), other.end())
		{

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

		//assignment operators
		vector& operator=(const vector& other)
		{
			if (&other != this) {
				size_t size = other.size();
				delete[] m_first;
				m_first = new Type[size];
				std::copy(other.begin(), other.end(), m_first);
				m_last = m_first + size;
			}
			return *this;
		}

		vector& operator=(vector&& other)
		{
			if (&other != this) {
				delete[] m_first;
				m_first = other.begin();
				m_last = other.end();
				other.m_first = nullptr;
				other.m_last = nullptr;
			}
			return *this;
		}

		// assign method
		template <typename InputIterator>
		void assign(InputIterator first, InputIterator last)
		{
			size_t size = last - first;
			delete[] m_first;
			m_first = new Type[size];
			std::copy(first, last, m_first);
			m_last = m_first + size;
		}

		// resize methods
		void resize(size_t count)
		{
			if (count == m_last - m_first)
				return;
			size_t size = this->size();
			Type* data = new Type[size];
			std::copy(m_first, m_last, data);
			delete[] m_first;
			m_first = new Type[count];
			m_last = m_first + count;
			if (count > size) {
				std::copy(data, data + size, m_first);
			}
			else {
				std::copy(data, data + count, m_first);
			}// implement this

			delete[] data;
		}


		iterator erase(const_iterator pos)
		{
			size_t pos_index = pos - m_first;
			for (size_t i = pos_index; i < size() - 1; i++) {
				m_first[i] = m_first[i + 1];
			}
			m_last--;
			resize(size());
			return m_first + pos_index;
		}

		iterator erase(const_iterator first, const_iterator last)
		{
			iterator tmp = const_cast<iterator>(first);
			for (size_t i = 0, between = last - first; i < between; ++i) {
				tmp = erase(tmp);
			}
			return tmp;
		}

		//insert methods
		iterator insert(const_iterator pos, const Type& value)
		{
			size_t size = m_last - m_first;
			size_t ptr = pos - m_first;
			Type* data = new Type[size];
			std::copy(m_first, m_last, data);
			delete[] m_first;
			m_first = new Type[size + 1];
			m_last = m_first + size + 1;
			std::copy(data, data + ptr, m_first);
			*(m_first + ptr) = value;
			std::copy(data + ptr, data + size, m_first + ptr + 1);
			return m_first + ptr;// implement this
		}

		template <typename InputIterator>
		iterator insert(const_iterator pos, InputIterator first, InputIterator last)
		{
			size_t size = m_last - m_first;
			size_t dif = last - first;
			size_t ptr = pos - m_first;
			Type* data = new Type[size];
			std::copy(m_first, m_last, data);
			delete[] m_first;
			m_first = new Type[size + dif];
			m_last = m_first + size + dif;
			std::copy(data, data + ptr, m_first);
			std::copy(first, last, m_first + ptr);
			std::copy(data + ptr, data + size, m_first + ptr + dif);
			return m_first + ptr;
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

		friend vector operator + (vector& a, vector& b) {
			vector <Type> c(a.size() + b.size());
			std::copy(a.m_first, a.m_last, c.m_first);
			std::copy(b.m_first, b.m_last, c.m_first + a.size());
			return c;
		}

/*		friend vector operator+(vector& a, vector& b) {
			size_t size = a.size() + b.size();
			vector <Type> vec = vec.concat(a, b);
			qsort(vec.m_first, vec.size(), sizeof(Type), comp);
			cout << endl;
			iterator tmp = vec.m_first;
			iterator tmp_next = vec.m_first + 1;
			for (size_t i = 0; (tmp_next + i) != vec.end(); i++) {
				if (*(tmp + i) == *(tmp_next + i)) {
					vec.erase(tmp_next + i);
				}
			}
			cout << this->at(4);
			
			return vector(vec);
		}
/*		vector unique_concat(vector& a, vector& b, int (*comp)(const void*, const void*)) {
			size_t size = a.size() + b.size();
			vector <Type> vec = vec.concat(a, b);
			qsort(vec.m_first, vec.size(), sizeof(Type), comp);
			cout << endl;
			iterator tmp = vec.m_first;
			iterator tmp_next = vec.m_first + 1;
			for (size_t i = 0; (tmp_next + i) != vec.end(); i++) {
				if (*(tmp + i) == *(tmp_next + i)) {
					vec.erase(tmp_next + i);
				}
			}
			return vec;
		}
*/
	private:
		reference checkIndexAndGet(size_t pos) const
		{
			if (pos >= size())
			{
				throw std::out_of_range("out of range");
			}

			return m_first[pos];
		}

	private:
		iterator m_first;
		iterator m_last;
	};
}//namespace stepic


	/*int main() {
		setlocale(LC_ALL, "Russian");
		stepic::vector<int> a = {1, 2, 3, 4, 5, 6};
		stepic::vector<int> b = { 4, 5, 6, 7, 8};
		cout << "1 вектор: ";
		for (size_t i = 0; i < a.size(); i++) {
			cout << a.at(i) << ",";
		}
		cout << endl;
		cout << "2 вектор: ";
		for (size_t i = 0; i < b.size(); i++) {
			cout << b.at(i) << ",";
		}
		cout << endl;
		stepic::vector<int> vec;
		vec = a + b;
	
		cout << "Умная конкатенация:" << endl;
		for (size_t i = 0; i < vec.size(); i++) {
			cout << vec.at(i) << ",";
		}

	/*	a = (a, b);
		cout << endl << "Просто конкатенция:" << endl;
		for (size_t i = 0; i < a.size(); i++) {
			cout << a.at(i) << ",";
		}
		

		return 0;
	}*/