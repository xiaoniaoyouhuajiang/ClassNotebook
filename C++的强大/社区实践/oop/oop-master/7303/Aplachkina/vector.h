

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

		explicit vector(size_t count = 0) {

			if (count) {
				m_first = new Type[count]();
				m_last = m_first + count;
				return;
			}

			m_first = nullptr;
			m_last = nullptr;
		}

		template <typename InputIterator>
		vector(InputIterator first, InputIterator last) {

			difference_type size = last - first;

			if (size <= 0) {
				m_first = nullptr;
				m_last = nullptr;
				return;
			}
			m_first = new Type[size];
			for (size_t i = 0; i < size; i++)
				m_first[i] = *first++;
			m_last = m_first + size;
		}

		vector(std::initializer_list <Type> init)
		{
			if (!init.size()) {
				m_first = nullptr;
				m_last = nullptr;
				return;
			}
			m_first = new Type[init.size()];
			for (size_t i = 0; i < init.size(); i++)
				m_first[i] = *init++;
			m_last = m_first + init.size();
		}

		vector(const vector& other) {

			if (!other.size()) {
				m_first = nullptr;
				m_last = nullptr;
				return;
			}
			m_first = new Type[other.size()];
			for (size_t i = 0; i < other.size(); i++)
				m_first[i] = other.m_first[i];
			m_last = m_first + other.size();
		}

		vector(vector&& other)
		{
			m_first = other.begin();
			m_last = other.end();

			other.m_first = nullptr;
			other.m_last = nullptr;
		}

		~vector()
		{
			if (!empty()) {
				delete[] m_first;
			}
		}

		vector& operator=(const vector& other) {

			if (m_first == other.begin()) {

				return *this;
			}
			delete[] m_first;
			m_first = new Type[other.size()];
			std::copy(other.begin(), other.end(), m_first);
			m_last = m_first + other.size();

			return *this;
		}

		vector& operator=(vector&& other) {

			if (m_first == other.begin()) {
				return *this;
			}
			delete[] m_first;
			m_first = other.begin();
			m_last = other.end();
			other.m_first = nullptr;
			other.m_last = nullptr;

			return *this;
		}

		// assign method
		template <typename InputIterator>
		void assign(InputIterator first, InputIterator last) {
			difference_type size = last - first;
			delete[] m_first;
			m_first = new Type[size];
			std::copy(first, last, m_first);
			m_last = m_first + size;
		}

		// resize methods
		void resize(size_t count)
		{
			iterator vec = new Type[count];
			if (count > m_last - m_first)
			{
				std::copy(m_first, m_last, vec);
			}
			else
			{
				std::copy(m_first, m_first + count, vec);
			}
			delete[]m_first;
			m_first = vec;
			m_last = m_first + count;
		}

		//erase methods
		iterator erase(const_iterator pos)
		{
			iterator iter = m_first;
			difference_type size = m_last - m_first;
			size_t i = 0;

			while (iter != pos) {
				iter++;
				i++;
			}
			std::rotate(iter, iter + 1, m_last);

			resize(size - 1);
			return  m_first + i;
		}

		iterator erase(const_iterator first, const_iterator last)
		{
			difference_type  n = last - first;
			iterator iter = m_first;

			if (n == 0) 
				return iter;

			for (; iter != first; iter++);
			for (size_t i = 0; i < n; i++) {
				iter = erase(iter);
			}
			return iter;
		}

		//insert methods
		iterator insert(const_iterator pos, const Type& value)
		{
			iterator iter = m_first;
			size_t i = 0;

			while (iter != pos) {
				iter++;
				i++;
			}
			resize(size() + 1);
			std::rotate(m_first + i, m_last - 1, m_last);
			m_first[i] = value;
			return  m_first + i;
		}

		template <typename InputIterator>
		iterator insert(const_iterator pos, InputIterator first, InputIterator last)
		{
			difference_type  n = last - first;

			iterator iter = m_first;
			size_t i = 0, index;

			while (iter != pos) {
				iter++;
				i++;
			}

			while (first != las) {
				push_back(*first);
				first++;
			}

			std::rotate(m_first + i, m_last - n, m_last);
			return m_first + i;
		}

		//push_back methods
		void push_back(const value_type& value)
		{
			resize(size() + 1);
			*(m_last - 1) = value;
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

