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

		explicit vector(size_t count = 0):
		m_first(count ? new value_type [count] : nullptr),
		m_last(m_first ? m_first + count : nullptr)
		{
	 
		}

		template <typename InputIterator>
		vector(InputIterator first, InputIterator last) : vector(last - first)
		{
			assign(first, last);
		}

		vector(std::initializer_list<Type> init) : vector(init.begin(), init.end())
		{
		}

		vector(const vector& other) : vector(other.m_first, other.m_last)
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
			if (m_first)
				delete [] m_first;
		}

		//assignment operators
		vector& operator=(const vector& other) 
		{
			assign(other.m_first, other.m_last);
		}


		vector& operator=(vector&& other)
		{
			if (m_first)
				delete [] m_first;
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
			size_t count = last - first;
		  	iterator new_arr = new value_type [count];
		  	try {
				std::copy(first, last, new_arr);
			  	if (m_first)
					delete [] m_first;
			  	m_first = new_arr;
			  	m_last = m_first + count;
		  	}
		  	catch(...) {
				delete[] new_arr;
				throw;
			}
		}

		// resize methods
		void resize(size_t count)
		{
			if (count == size())
				return;
			
			iterator new_arr = count ? new Type[count] : nullptr;
			try {

				std::copy(m_first, m_first + std::min(count, size()), new_arr);
				delete [] m_first;
				m_first = new_arr;
				m_last = m_first + count;
			}
			catch (...) {
				delete [] new_arr;
				throw;
			}
		}

		//erase methods
		iterator erase(const_iterator pos)
		{ 
			std::rotate((iterator)pos, (iterator)pos + 1, m_last);
			size_t index = pos - m_first;
			resize(size() - 1);
			return m_first + index;
		}

		iterator erase(const_iterator first, const_iterator last)
		{
			std::rotate((iterator)first, (iterator)last, m_last);
			size_t index = first - m_first;
			resize(size() - (last - first));
			return m_first + index;
		}

		//insert methods
		iterator insert(const_iterator pos, const Type& value)
		{
			size_t index = pos - m_first;
			resize(size() + 1);
			m_first[size() - 1] = value;
			std::rotate((iterator)(m_first + index), m_last, m_last);
			return m_first + index;
		}

		template <typename InputIterator>
		iterator insert(const_iterator pos, InputIterator first, InputIterator last)
		{
			size_t index = pos - m_first;
			size_t old_size = size();
			resize(size() + last - first);
			std::copy(first, last, m_first + old_size);
			std::rotate((iterator)(m_first + index), (iterator)(m_first + old_size), m_last);
			return m_first + index;
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

using namespace stepik;

int main()
{
	vector<char> v;

	return 0;
}