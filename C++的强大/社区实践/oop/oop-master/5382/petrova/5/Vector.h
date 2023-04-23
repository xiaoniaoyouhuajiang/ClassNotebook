#include <assert.h>
#include <algorithm> // std::copy, std::rotate
#include <cstddef> // size_t
#include <initializer_list>
#include <stdexcept>


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
			if (count == 0)
			{
				m_first = NULL;
				m_last = NULL;
			}
			else {
				m_first = new Type[count];
				m_last = m_first + count;
			}
			// use previous step implementation
		}

		template <typename InputIterator>
		vector(InputIterator first, InputIterator last) :vector(last - first)// made [first, last) copied
		{
			std::copy(first, last, m_first);
			// use previous step implementation
		}

		vector(std::initializer_list<Type> init) : vector(init.begin(), init.end())
		{
			// use previous step implementation
		}

		vector(const vector& other)
		{
			size_t count = other.size();
			m_first = new Type[count];
			m_last = m_first + count;
			std::copy(other.m_first, other.m_last, m_first);
			// use previous step implementation
		}

		vector(vector&& other)
		{
			m_first = other.m_first;
			m_last = other.m_last;
			other.m_first = NULL;
			other.m_last = NULL;
			// use previous step implementation
		}

		~vector()
		{
			delete[] m_first;
			// use previous step implementation
		}


		//insert methods
		iterator insert(const_iterator pos, const Type& value)//Вставляет value перед элементом, на который указывает pos.
		{
			iterator quontity = (iterator)& value;
			return insert(pos, quontity, quontity + 1);

			// implement this
		}

		template <typename InputIterator>
		iterator insert(const_iterator pos, InputIterator first, InputIterator last)// Вставляет элементы из диапазона [first, last) перед элементом, на который указывает pos.
		{
			int count = last - first;
			int Nsize = count + size();
			Type* Ntype = new Type[Nsize];
			std::copy(m_first, (iterator)pos, Ntype);//copy first part till insertPart
			int sizeFirst = pos - m_first;
			int countFirst = 0;
			for (int i = sizeFirst; i<Nsize; i++)//copy insertPart
			{
				Ntype[i] = first[countFirst];
				countFirst++;
			}
			for (int t = sizeFirst + count; t<Nsize; t++)//copy end part
			{
				Ntype[t] = m_first[t - count];
			}
			delete[] m_first;
			m_first = Ntype;
			m_last = Ntype + Nsize;
			return m_first + sizeFirst;
			// implement this
		}

		//push_back methods
		void push_back(const value_type& value)
		{
			insert(m_last, value);
			// implement this
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

