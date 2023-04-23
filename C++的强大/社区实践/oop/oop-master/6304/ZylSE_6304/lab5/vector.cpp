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

		explicit vector(size_t count = 0)
		{
			if (count <= 0) {
				m_first = m_last = nullptr;
			}
			else {
				m_first = new Type[count];
				m_last = m_first + count;
			}
		}

		template <typename InputIterator>
		vector(InputIterator first, InputIterator last) // Создает контейнер с содержимым диапазона [first, last)
		{
			difference_type count = last - first;
			if (count) {
				m_first = new Type[count];
				m_last = m_first + count;
				std::copy(first, last, m_first);
			}
			else {
				m_first = m_last = nullptr;
			}
		}

		vector(std::initializer_list<Type> init)//Создает контейнер с содержимым списка инициализации init
		{
			size_t count = init.size();
			if (!count)
				m_first = m_last = nullptr;
			else {
				m_first = new Type[count];
				m_last = m_first + count;
				std::copy(init.begin(), init.end(), m_first);
			}
		}

		vector(const vector& other)//Конструктор копирования. Создает контейнер с копией содержимого other
		{
			size_t count = other.size();
			if (!count)
				m_first = m_last = nullptr;
			else {
				m_first = new Type[count];
				m_last = m_first + count;
				std::copy(other.m_first, other.m_last, m_first);
			}
		}

		vector(vector&& other)//Конструктор перемещения. Создает контейнер с содержимым other путём перемещения данных
		{
			m_first = other.m_first;
			m_last = other.m_last;
			other.m_first = other.m_last = nullptr;
		}

		~vector()//Деструктор
		{
			if (!empty()) {
				delete[] m_first;
			}
		}

		//assignment operators
		vector& operator=(const vector& other)
		{
			if (!empty()) {
				delete[] m_first;
			}
			size_t count = other.size();
			if (count) {
				m_first = new Type[count];
				m_last = m_first + count;
				std::copy(other.m_first, other.m_last, m_first);
			}
			else {
				m_first = m_last = nullptr;
			}
			return *this;
		}

		vector& operator=(vector&& other)
		{
			if (!empty()) {
				delete[] m_first;
			}
			m_first = other.m_first;
			m_last = other.m_last;
			other.m_first = other.m_last = nullptr;

			return *this;
		}

		// assign method
		template <typename InputIterator>
		void assign(InputIterator first, InputIterator last)
		{
			if (!empty()) {
				delete[] m_first;
			}
			difference_type count = last - first;
			if (count) {
				m_first = new Type[count];
				m_last = m_first + count;
				std::copy(first, last, m_first);
			}
			else {
				m_first = m_last = nullptr;
			}
		}

		// resize methods
		void resize(size_t count)
		{
			if (count && count != size()) {
				iterator item = new Type[count];
				if (count>size()) {
					std::copy(m_first, m_last, item);
				}
				else {
					std::copy(m_first, m_first + count, item);
				}
				if (!empty()) {
					delete[] m_first;
				}
				m_first = item;
				m_last = m_first + count;
			}
			else if (!count && count != size()) {
				delete[] m_first;
				m_last = m_first = nullptr;
			}
		}

		//erase methods
		iterator erase(const_iterator pos)
		{
			if (pos < m_first || pos > m_last)
			{
				throw std::out_of_range("out of range");
			}
			difference_type for_rem = pos - m_first;
			std::rotate(m_first + for_rem, m_first + for_rem + 1, m_last);
			resize(size() - 1);
			return m_first + for_rem;
		}

		iterator erase(const_iterator first, const_iterator last)
		{
			if (first < m_first || last > m_last || first > m_last || last < m_first)
			{
				throw std::out_of_range("out of range");
			}
			difference_type for_rem = first - m_first;
			difference_type len_for_rem = last - first;
			std::rotate(m_first + for_rem, m_first + for_rem + len_for_rem, m_last);
			resize(size() - len_for_rem);
			return m_first + for_rem;
		}

		//insert methods
		iterator insert(const_iterator pos, const Type& value)
		{

			iterator item = new Type[size() + 1];
			difference_type for_insert = pos - m_first;
			std::copy(m_first, m_first + for_insert, item);
			item[for_insert] = value;
			std::copy(m_first + for_insert, m_last, item + for_insert + 1);

			m_last = item + size() + 1;
			if (m_first)
				delete[] m_first;
			m_first = item;

			return m_first + for_insert;
		}

		template <typename InputIterator>
		iterator insert(const_iterator pos, InputIterator first, InputIterator last)
		{

			difference_type for_insert = pos - m_first;
			difference_type len = last - first;
			iterator item = new Type[size() + len];
			std::copy(m_first, m_first + for_insert, item);
			std::copy(first, last, item + for_insert);
			std::copy(m_first + for_insert, m_last, item + for_insert + len);

			m_last = item + size() + len;
			if (m_first)
				delete[] m_first;
			m_first = item;


			return m_first + for_insert;
		}

		//push_back methods
		void push_back(const value_type& value)
		{

			iterator item = new Type[size() + 1];
			std::copy(m_first, m_last, item);
			item[size()] = value;

			m_last = item + size() + 1;
			if (m_first)
				delete[] m_first;
			m_first = item;

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