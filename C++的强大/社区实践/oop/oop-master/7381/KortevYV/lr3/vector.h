#include <assert.h>
#include <algorithm> // std::copy, std::rotate
#include <cstddef> // size_t
#include <initializer_list>
#include <stdexcept>

namespace stepik
{
	template <class Type>
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
			m_first = new Type[count];
			m_last = m_first + count;
		}

		template <typename InputIterator>
		vector(InputIterator first, InputIterator last) {
			size_t count;
			count = last - first;
			m_first = new Type[count];
			m_last = m_first + count;
			std::copy(first, last, m_first);
		}

		vector(std::initializer_list <Type> init) : vector(init.begin(), init.end()) {}

		vector(const vector& other) : vector(other.begin(), other.end()) {}

		vector(vector&& other) {
			m_first = other.m_first;
			m_last = other.m_last;
			other.m_first = nullptr;
			other.m_last = nullptr;
		}

		//assignment operators
		vector& operator=(const vector& other) {
			if (this != &other) {
				delete[] m_first;
				size_t count = other.m_last - other.m_first;
				m_first = new Type[count];
				m_last = m_first + count;
				std::copy(other.m_first, other.m_last, m_first);
				return *this;
			}
		}

		vector& operator=(vector&& other) {
			if (this != &other) {
				delete[] m_first;
				m_first = other.m_first;
				m_last = other.m_last;
				other.m_first = nullptr;
				other.m_last = nullptr;
				return *this;
			}
		}

		~vector() {
			delete[] m_first;
		}

		//insert methods
		iterator insert(const_iterator pos, const Type& value)
		{
			size_t num = pos - m_first;
			vector temp(*this);
			delete[]m_first;
			m_first = new value_type[temp.size() + 1];
			m_last = m_first + temp.size() + 1;
			std::copy(temp.begin(), temp.begin() + num, m_first);
			*(m_first + num) = value;
			std::copy(temp.begin() + num, temp.end(), m_first + num + 1);
			return m_first + num;
		}

		template <typename InputIterator>
		iterator insert(const_iterator pos, InputIterator first, InputIterator last)
		{
			size_t num = pos - m_first;
			size_t count = last - first;
			vector temp(*this);
			delete[]m_first;
			m_first = new value_type[temp.size() + last - first];
			m_last = m_first + temp.size() + (last - first);
			std::copy(temp.begin(), temp.begin() + num, m_first);
			std::copy(first, last, m_first + num);
			std::copy(temp.begin() + num, temp.end(), m_first + num + count);
			return num + m_first;
		}

#include <assert.h>
#include <algorithm> // std::copy, std::rotate
#include <cstddef> // size_t
#include <initializer_list>
#include <stdexcept>

		namespace stepik
		{
			template <class Type>
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
					m_first = new Type[count];
					m_last = m_first + count;
				}

				template <typename InputIterator>
				vector(InputIterator first, InputIterator last) {
					size_t count;
					count = last - first;
					m_first = new Type[count];
					m_last = m_first + count;
					std::copy(first, last, m_first);
				}

				vector(std::initializer_list <Type> init) : vector(init.begin(), init.end()) {}

				vector(const vector& other) : vector(other.begin(), other.end()) {}

				vector(vector&& other) {
					m_first = other.m_first;
					m_last = other.m_last;
					other.m_first = nullptr;
					other.m_last = nullptr;
				}

				//assignment operators
				vector& operator=(const vector& other) {
					if (this != &other) {
						delete[] m_first;
						size_t count = other.m_last - other.m_first;
						m_first = new Type[count];
						m_last = m_first + count;
						std::copy(other.m_first, other.m_last, m_first);
						return *this;
					}
				}

				vector& operator=(vector&& other) {
					if (this != &other) {
						delete[] m_first;
						m_first = other.m_first;
						m_last = other.m_last;
						other.m_first = nullptr;
						other.m_last = nullptr;
						return *this;
					}
				}

				~vector() {
					delete[] m_first;
				}

				// resize methods
				void resize(size_t count)
				{
					vector temp(*this);
					delete[]m_first;
					m_first = new value_type[count];
					m_last = m_first + count;
					std::copy(temp.begin(), count < temp.end() - temp.begin() ? temp.begin() + count : temp.end(), m_first);
				}

				//erase methods
				iterator erase(const_iterator pos)
				{
					size_t num = pos - m_first;
					std::rotate(const_cast<iterator>(pos), const_cast<iterator>(pos) + 1, m_last);
					resize(size() - 1);
					return m_first + num;
				}

				iterator erase(const_iterator first, const_iterator last)
				{
					iterator del = const_cast<iterator>(first);
					for (size_t i = 0; i < last - first; i++)
						del = erase(del);
					return del;
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

		//push_back methods
		void push_back(const value_type& value)
		{
			insert(this->end(), value);
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