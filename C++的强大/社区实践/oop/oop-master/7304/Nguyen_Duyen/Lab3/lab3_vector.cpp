#include <assert.h>
#include <iostream>
#include <algorithm> // std::copy, std::rotate
#include <cstddef> // size_t
#include <initializer_list>
#include <stdexcept>

using namespace std;

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
			// implement this
			m_first = new Type[count];
			m_last = m_first + count;
			for (size_t i = 0; i < count; i++) {
				m_first[i] = 0;
			}

		}

		template <typename InputIterator>
		vector(InputIterator first, InputIterator last)
		{
			// implement this
			size_t count = last - first;
			if (count > 0) {
				m_first = new Type[count];
				m_last = m_first + count;
				copy(first, last, m_first);
			}
			else {
				m_first = nullptr;
				m_last = nullptr;
			}
		}

		vector(std::initializer_list<Type> init)
		{
			// implement this
			size_t count = init.size();
			if (count > 0) {
				m_first = new Type[count];
				m_last = m_first + count;
				copy(init.begin(), init.end(), m_first);
			}
		}

		vector(const vector& other)
		{
			// implement this
			size_t count = other.size();
			if (count > 0) {
				m_first = new Type[count];
				m_last = m_first + count;
				copy(other.begin(), other.end(), m_first);
			}
			else {
				m_first = nullptr;
				m_last = nullptr;
			}
		}

		vector(vector&& other)
		{
			// implement this
			m_first = other.m_first;
			m_last = other.m_last;
			other.m_first = nullptr;
			other.m_last = nullptr;
		}

		~vector()
		{
			// implement this
			delete[] m_first;
		}

		//assignment operators
		vector& operator=(const vector& other)
		{
			// implement this
			delete[] m_first;
			size_t count = other.size();
			if (count > 0) {
				m_first = new Type[count];
				m_last = m_first + count;
				copy(other.begin(), other.end(), m_first);
			}
			else {
				m_first = nullptr;
				m_last = nullptr;
			}	
		}

		vector& operator=(vector&& other)
		{
			// implement this
			delete[] m_first;
			this->m_first = other.m_first;
			this->m_last = other.m_last;
			other.m_first = nullptr;
			other.m_last = nullptr;
			return *this;
		}

		// assign method
		template <typename InputIterator>
		void assign(InputIterator first, InputIterator last)
		{
			// implement this
			delete[] m_first;
			size_t count = last - first;
			if (count > 0) {
				m_first = new Type[count];
				m_last = m_first + count;
				copy(first, last, m_first);
			}
			else {
				m_first = nullptr;
				m_last = nullptr;
			}
		}

		// resize methods
		void resize(size_t count)
		{
			// implement this
			if (count == size())
				return;
			iterator temp = new Type[count];
			if(count > size()) {
				copy(m_first, m_last, temp);
			}
			else {
				copy(m_first, m_first + count, temp);
			}
			delete[] m_first;
			m_first = temp;
			m_last = m_first + count;
		}

		//erase methods
		iterator erase(const_iterator pos)
		{
			// implement this
			size_t p = pos - m_first;
			for (size_t i = p; i < size() - 1; i++) {
				m_first[i] = m_first[i + 1];
			}
			resize(size() - 1);
			return m_first + p;
		}

		iterator erase(const_iterator first, const_iterator last)
		{
			// implement this
			size_t p = first - m_first;
			size_t count = last - first;
			for (size_t i = p; i < size() - count; i++) {
				m_first[i] = m_first[i + count];
			}
			resize(size() - count);
			return m_first + p;
		}

		//insert methods
		iterator insert(const_iterator pos, const Type& value)
		{
			// implement this
			size_t p = pos - m_first;
			resize(size() + 1);
			for (size_t i = size() - 1; i > p; i--) {
				m_first[i] = m_first[i - 1];
			}

			m_first[p] = value;
			return m_first + p;
		}

		template <typename InputIterator>
		iterator insert(const_iterator pos, InputIterator first, InputIterator last)
		{
			// implement this
			iterator p = const_cast<iterator>(pos);
			size_t count = last - first;
			resize(size() + count);
			while (count) {
				count--;
				p = insert(p, first + count);
			}
			return p;
		}

		//push_back methods
		void push_back(const value_type& value)
		{
			// implement this
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

int main() 
{
	stepik::vector<int> vec(10);
	for (size_t i = 0; i < vec.size(); i++) {
		vec[i] = i + 1;
	}
	cout << "Vector: ";
	for (size_t i = 0; i < vec.size(); i++) {
		cout << vec[i] << " ";
	}cout << endl;

	vec.erase(vec.begin()+2);
	cout << "Erase: ";
	for (size_t i = 0; i < vec.size(); i++) {
		cout << vec[i] << " ";
	}cout << endl;

	system("pause");
	return 0;
}