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
			if (count == 0){
				m_first = nullptr;
				m_last = nullptr;
			}
			else{
				my_f(count);
			}
		}

		template <typename InputIterator>
		vector(InputIterator first, InputIterator last) : vector(last - first)
		{
			std::copy(first, last, m_first);
		}

		vector(std::initializer_list<Type> init)
		{
			vector(init.begin(), init.end());
		}

		vector(const vector& other)
		{
			my_f(other.size());
			try {
				std::copy(other.m_first, other.m_last, m_first);
			}
			catch (...){
				delete[] m_first;
				throw;
			}
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
			return *this = std::move(vector<Type>(other));
		}

		vector& operator=(vector&& other)
		{
			delete[] m_first;
			m_first = other.m_first;
			m_last = other.m_last;
			other.m_first = other.m_last = nullptr;
			return *this;
		}

		// assign method
		template <typename InputIterator>
		void assign(InputIterator first, InputIterator last)
		{
			*this = std::move(vector<Type>(first, last));
		}

		// resize methods
		void resize(size_t count)
		{
			iterator end = (count > size()) ? m_last : m_first + count;

			vector new_vector(count);
			std::move(m_first, end, new_vector.m_first);

			std::swap(m_first, new_vector.m_first);
			std::swap(m_last, new_vector.m_last);
		}

		//erase methods
		iterator erase(const_iterator pos)
		{
			iterator pos2 = const_cast<iterator>(pos);
			size_t sz = pos - m_first;

			std::rotate(pos2, pos2 + 1, m_last);
			resize(size() - 1);

			return (m_first + sz);
		}

		iterator erase(const_iterator first, const_iterator last)
		{
			size_t count = last - first;

			iterator a = const_cast<iterator>(first);

			while (count)
			{
				a = erase(a);
				count--;
			}

			return a;
		}

		//insert methods
		iterator insert(const_iterator pos, const Type& value)
		{
			size_t n = pos - m_first;
			resize(size() + 1);

			iterator pos2 = m_first + n;
			std::rotate(pos2, m_last - 1, m_last);
			*pos2 = value;

			return pos2;
		}

		template <typename InputIterator>
		iterator insert(const_iterator pos, InputIterator first, InputIterator last)
		{
			size_t count = last - first;
			iterator p = const_cast<iterator>(pos);

			while (count)
			{
				p = insert(p, first[--count]);
			}

			return p;
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

	private:
		void my_f(size_t sz){
			m_first = new Type[sz];
			m_last = m_first + sz;
		}

		iterator m_first;
		iterator m_last;
	};
}// namespace stepik